//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <gui/set/console_panel.hpp>
#include <gui/set/window.hpp>
#include <gui/control/text_ctrl.hpp>
#include <gui/util.hpp>
#include <util/window_id.hpp>
#include <data/stylesheet.hpp>
#include <data/card.hpp>
#include <wx/splitter.h>
#include <wx/dcbuffer.h>
#include <wx/clipbrd.h>

DECLARE_POINTER_TYPE(ConsoleMessage);

// ----------------------------------------------------------------------------- : MessageControl

class ConsoleMessage : public IntrusivePtrBase<ConsoleMessage> {
public:
  MessageType type;
  String text; // string message
  wxDateTime timestamp;
  Bitmap bitmap; // image message instead of string
  ScriptValueP value; // other valued message (images? cards?)
  // location of error messages
  String source_file;
  int line_number;
  // layout
  bool joined_to_previous;
  int top;
  int height;
  int bottom() const { return top+height; }
  
  ConsoleMessage(MessageType type, String const& text = _(""), bool joined_to_previous = false)
    : type(type), text(text), timestamp(wxDateTime::Now()), line_number(-1), joined_to_previous(joined_to_previous), top(-1), height(-1)
  {}
};

class MessageCtrl : public wxControl {
public:
  MessageCtrl(wxWindow* parent, int id)
    : wxControl(parent, id, wxDefaultPosition, wxDefaultSize, wxBORDER_THEME | wxWANTS_CHARS | wxVSCROLL)
  {
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    // icons
    static_assert(MESSAGE_TYPE_MAX == 7);
    icons[MESSAGE_NONE]    = wxBitmap();
    icons[MESSAGE_INPUT]   = wxBitmap(load_resource_image(_("message_input")));
    icons[MESSAGE_OUTPUT]  = wxBitmap();
    icons[MESSAGE_INFO]    = wxBitmap(load_resource_image(_("message_information")));
    icons[MESSAGE_WARNING] = wxBitmap(load_resource_image(_("message_warning")));
    icons[MESSAGE_ERROR]   = wxBitmap(load_resource_image(_("message_error")));
    icons[MESSAGE_FATAL_ERROR] = icons[MESSAGE_ERROR];
    // color
    colors[MESSAGE_INPUT]   = wxColour(0,80,0);
    colors[MESSAGE_OUTPUT]  = wxColour(255,255,255);
    colors[MESSAGE_INFO]    = wxColour(0,0,255);
    colors[MESSAGE_WARNING] = wxColour(255,255,0);
    colors[MESSAGE_ERROR]   = colors[MESSAGE_FATAL_ERROR] = wxColour(255,0,0);
    // scrollbar
    update_scrollbar();
  }
  
  void add_message(ConsoleMessageP const& msg) {
    messages.push_back(msg);
    layout_all(messages.size() - 1);
    // clear selection
    selection = messages.size();
    // refresh
    ensure_visible(*messages.back());
    update_scrollbar();
    Refresh(false);
  }
  void add_message(MessageType type, String const& text, bool joined_to_previous = false) {
    add_message(make_intrusive<ConsoleMessage>(type,text,joined_to_previous));
  }

  void clear_console() {
    messages.clear();
    layout_all();
    selection = messages.size();
    update_scrollbar();
    Refresh(false);
  }
  
  bool have_selection() const {
    return selection < messages.size();
  }
  
  bool canCopy() const {
    return have_selection();
  }
  bool doCopy() {
    if (selection >= messages.size()) return false;
    ConsoleMessage const& msg = *messages[selection];
    if (!wxTheClipboard->Open()) return false;
    bool ok = false;
    if (msg.bitmap.Ok()) {
      ok = wxTheClipboard->SetData(new wxBitmapDataObject(msg.bitmap));
    } else {
      ok = wxTheClipboard->SetData(new wxTextDataObject(msg.text));
    }
    wxTheClipboard->Close();
    return ok;
  }
  
  bool AcceptsFocus() const override {
    return true;
  }

private:
  DECLARE_EVENT_TABLE();
  
  // --------------------------------------------------- : Data
  
  // the messages
  vector<ConsoleMessageP> messages;
  size_t selection;
  wxBitmap icons[MESSAGE_TYPE_MAX];
  wxColour colors[MESSAGE_TYPE_MAX];
  
  // --------------------------------------------------- : Events
  
  void select(size_t sel) {
    selection = sel;
    if (selection < messages.size()) {
      ensure_visible(*messages[selection]);
    }
    Refresh(false);
  }
  
  void onLeftDown(wxMouseEvent& ev) {
    select(find_point(view_start + ev.GetY()));
    ev.Skip(); // for focus
  }
  
  void onChar(wxKeyEvent& ev) {
    switch (ev.GetKeyCode()) {
      case WXK_UP:
        if (selection < messages.size() && selection > 0) select(selection - 1);
        break;
      case WXK_DOWN:
        if (selection < messages.size() && selection + 1 < messages.size()) select(selection + 1);
        break;
      case WXK_HOME:
        if (!messages.empty()) select(0);
        break;
      case WXK_END:
        if (!messages.empty()) select(messages.size() - 1);
        break;
      case WXK_TAB:
        Navigate(ev.ShiftDown() ? wxNavigationKeyEvent::IsBackward : wxNavigationKeyEvent::IsForward);
        break;
      default:
        ev.Skip();
    }
  }
  
  void onFocus(wxFocusEvent& ev) {
    if (selection < messages.size()) Refresh(false);
    ev.Skip();
  }
  
  size_t find_point(int y) {
    // TODO: could do a binary search here
    for (size_t i = 0 ; i < messages.size() ; ++i) {
      if (y >= messages[i]->top && y < messages[i]->bottom()) return i;
    }
    return (size_t)-1;
  }
  
  void ensure_visible(ConsoleMessage const& msg) {
    int height = GetClientSize().y;
    if (msg.top < view_start) {
      scroll_to(msg.top);
    } else if (msg.bottom() > view_start + height) {
      scroll_to(msg.bottom() - height);
    }
  }

  // --------------------------------------------------- : Scrolling
  int view_start = 0; // y coordinate where the view starts

  void scroll_to(int new_view_start, bool update_scrollbar = true) {
    int bottom = messages.empty() ? 0 : messages.back()->bottom() - GetClientSize().y;
    view_start = new_view_start;
    view_start = min(bottom, view_start);
    view_start = max(0, view_start);
    if (update_scrollbar) {
      // update actual scrollbar
      this->update_scrollbar();
      // scroll actual window content
      Refresh(false);
    }
  }

  void update_scrollbar() {
    int screen_height = GetClientSize().y;
    int total_height = messages.empty() ? 0 : messages.back()->bottom();
    // update view_start to keep messages in view
    int bottom = total_height - GetClientSize().y;
    view_start = min(bottom, view_start);
    view_start = max(0, view_start);
    SetScrollbar(wxVERTICAL, view_start, screen_height, total_height);
  }

  void onScroll(wxScrollWinEvent& ev) {
    wxEventType type = ev.GetEventType();
    if (type == wxEVT_SCROLLWIN_TOP) {
      scroll_to(0);
    } else if (type == wxEVT_SCROLLWIN_BOTTOM) {
      scroll_to(INT_MAX);
    } else if (type == wxEVT_SCROLLWIN_LINEUP) {
      scroll_to(view_start - MIN_ITEM_HEIGHT);
    } else if (type == wxEVT_SCROLLWIN_LINEDOWN) {
      scroll_to(view_start + MIN_ITEM_HEIGHT);
    } else if (type == wxEVT_SCROLLWIN_PAGEUP) {
      scroll_to(view_start - GetClientSize().y*3/4);
    } else if (type == wxEVT_SCROLLWIN_PAGEDOWN) {
      scroll_to(view_start + GetClientSize().y*3/4);
    } else {
      scroll_to(ev.GetPosition());
    }
  }

  void onMouseWheel(wxMouseEvent& ev) {
    scroll_to(view_start - MIN_ITEM_HEIGHT * ev.GetWheelRotation() / ev.GetWheelDelta());
  }

  void onSize(wxSizeEvent&) {
    update_scrollbar();
    Refresh(false);
  }

  // --------------------------------------------------- : Drawing

  void onPaint(wxPaintEvent& ev) {
    wxAutoBufferedPaintDC dc(this);
    PrepareDC(dc);
    draw(dc);
  }

  void draw(wxDC& dc) const {
    clearDC(dc, wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
    dc.SetFont(*wxNORMAL_FONT);

    FOR_EACH_CONST(msg, messages) {
      draw(dc, *msg);
    }
    if (messages.empty()) {
      // Say something about no messages?
    }
  }
  
  void draw(wxDC& dc, ConsoleMessage const& msg) const {
    auto client_size = GetClientSize();
    if (msg.bottom() < view_start || msg.top > view_start + client_size.y) return; // out of view
    int left = 0;
    int top  = msg.top - view_start;
    int width = client_size.x;
    wxColour color = colors[msg.type];
    wxColour bg, fg;
    if (selection < messages.size() && messages[selection].get() == &msg) {
      if (FindFocus() == this) {
        bg = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT);
        fg = wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHTTEXT);
      } else {
        bg = lerp(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW), wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT), 0.1);
        fg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
      }
    } else {
      bg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW);
      fg = wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOWTEXT);
    }
    
    // draw background
    dc.SetPen(*wxTRANSPARENT_PEN);
    dc.SetBrush(lerp(bg,color, 0.05));
    dc.DrawRectangle(left,top,width,msg.height);

    // draw foreground
    dc.SetTextForeground(fg);

    // draw timestamp
    dc.DrawText(msg.timestamp.FormatISOTime(), left + TIMESTAMP_PADDING, top + TEXT_PADDING_TOP);

    int timestamp_resolved_width;
    dc.GetTextExtent(_("55:55:55"), &timestamp_resolved_width, nullptr);

    left += timestamp_resolved_width;
    left += TIMESTAMP_PADDING * 2;

    // draw line right of timestamp
    dc.SetPen(lerp(bg, fg, 0.3));
    dc.DrawLine(left, top, left, top + msg.height);

    // draw icon
    if (icons[msg.type].Ok()) {
      dc.DrawBitmap(icons[msg.type], left + ICON_PADDING_LEFT,top + ICON_PADDING);
    }
    
    // draw text
    int text_left = left + TEXT_PADDING_LEFT;
    int text_top  = top + TEXT_PADDING_TOP;
    // find line breaks in the text
    String::const_iterator begin = msg.text.begin();
    String::const_iterator it = begin;
    while (it != msg.text.end()) {
      if (*it == _('\n')) {
        // break here
        dc.DrawText(String(begin,it), text_left, text_top);
        begin = it = it + 1;
        text_top += dc.GetCharHeight() + TEXT_LINE_SPACING;
      } else {
        it++;
      }
    }
    if (begin != msg.text.end()) {
      dc.DrawText(String(begin,it), text_left, text_top);
      text_top += dc.GetCharHeight() + TEXT_LINE_SPACING;
    }
    
    // draw bitmap
    if (msg.bitmap.Ok()) {
      dc.DrawBitmap(msg.bitmap, text_left, text_top);
      text_top += msg.bitmap.GetHeight();
    }

    // draw line below item
    dc.SetPen(lerp(bg,fg, 0.3));
    dc.DrawLine(0, top + msg.height, 0 + width, top + msg.height);
  }
  
  int item_height(wxDC& dc, ConsoleMessage const& msg) const {
    // text height
    int text_height = 0;
    // find line breaks in the text
    String::const_iterator begin = msg.text.begin();
    String::const_iterator it = begin;
    while (it != msg.text.end()) {
      if (*it == _('\n')) {
        // break here
        begin = it = it + 1;
        text_height += dc.GetCharHeight() + TEXT_LINE_SPACING;
      } else {
        it++;
      }
      // TODO: break long lines
    }
    if (begin != msg.text.end()) {
      text_height += dc.GetCharHeight() + TEXT_LINE_SPACING;
    }

    // account for the height of a timestamp even if there is no other text content.
    if (text_height == 0) {
      text_height = dc.GetCharHeight() + TEXT_LINE_SPACING;
    }
    
    // height of bitmap
    int bitmap_height = msg.bitmap.Ok() ? msg.bitmap.GetHeight() : 0;
    
    return max(MIN_ITEM_HEIGHT, TEXT_PADDING_TOP + TEXT_PADDING_BOTTOM + text_height + bitmap_height) + LIST_SPACING;
  }
  
  // --------------------------------------------------- : Layout

  static constexpr int LIST_SPACING        = 1;
  static constexpr int TIMESTAMP_PADDING   = 3;
  static constexpr int ICON_PADDING        = 3;
  static constexpr int ICON_PADDING_LEFT   = TIMESTAMP_PADDING + 3;
  static constexpr int TEXT_PADDING_LEFT   = ICON_PADDING_LEFT + 16 + 4;
  static constexpr int TEXT_PADDING_RIGHT  = 4;
  static constexpr int TEXT_PADDING_TOP    = 4;
  static constexpr int TEXT_PADDING_BOTTOM = 2;
  static constexpr int TEXT_LINE_SPACING   = 1;
  static constexpr int MIN_ITEM_HEIGHT     = 16 + 2*ICON_PADDING;
  
  /// Layout all messages, starting from number start
  /// layout = determine their height
  void layout_all(size_t start = 0) {
    // scratch dc, for finding text sizes
    wxMemoryDC dc;
    wxBitmap bmp(1,1);
    dc.SelectObject(bmp);
    dc.SetFont(*wxNORMAL_FONT);
    
    for (size_t i = start ; i < messages.size() ; ++i) {
      // layout a single item
      ConsoleMessage& msg = *messages[i];
      msg.top = start == 0 ? 0 : messages[i-1]->bottom() + LIST_SPACING;
      if (i > 0 && msg.joined_to_previous) msg.top -= LIST_SPACING;
      // text size
      msg.height = item_height(dc, msg);
    }
    
    // set size of the control
    if (messages.empty()) {
      SetVirtualSize(-1, 0);
    } else {
      int height = messages.back()->bottom();
      SetVirtualSize(-1, height);
    }
  }
  
  // --------------------------------------------------- : Layout
  
};

BEGIN_EVENT_TABLE(MessageCtrl,wxScrolledWindow)
  EVT_PAINT(MessageCtrl::onPaint)
  EVT_LEFT_DOWN(MessageCtrl::onLeftDown)
  EVT_CHAR(MessageCtrl::onChar)
  EVT_SET_FOCUS(MessageCtrl::onFocus)
  EVT_KILL_FOCUS(MessageCtrl::onFocus)
  EVT_SCROLLWIN(MessageCtrl::onScroll)
  EVT_MOUSEWHEEL(MessageCtrl::onMouseWheel)
  EVT_SIZE(MessageCtrl::onSize)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------- : TextCtrl with history

class HistoryTextCtrl : public wxTextCtrl {
public:
  HistoryTextCtrl(wxWindow* parent, wxWindowID id)
    : wxTextCtrl(parent, id, _(""), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER)
    , history_pos(0)
  {}
  
  String get_command_and_clear() {
    String command = GetValue();
    history.push_back(command);
    history_pos = (int)history.size();
    SetValue(_(""));
    return command;
  }
  
private:
  DECLARE_EVENT_TABLE();
  vector<String> history; // TODO: save command history to settings?
  int history_pos; // position when browsing through history
  
  void onChar(wxKeyEvent& ev) {
    switch (ev.GetKeyCode()) {
      case WXK_UP:
        browse_history(-1);
        break;
      case WXK_DOWN:
        browse_history(+1);
        break;
      default:
        ev.Skip();
    }
  }
  
  // browse history for strings that share the part before the cursor with the current value in the control
  bool browse_history(int dir) {
    int caret = GetInsertionPoint();
    String to_match = GetValue().substr(0, caret);
    while (history_pos+dir >= 0 && history_pos+dir < (int)history.size()) {
      history_pos += dir;
      if (starts_with(history[history_pos],to_match)) {
        SetValue(history[history_pos]);
        SetInsertionPoint(caret);
        return true;
      }
    }
    if (dir > 0) {
      // there is a blank string at the end of the history
      SetValue(to_match);
      SetInsertionPoint(caret);
    }
    return false;
  }
};

BEGIN_EVENT_TABLE(HistoryTextCtrl,wxTextCtrl)
  EVT_CHAR(HistoryTextCtrl::onChar)
END_EVENT_TABLE()

// ----------------------------------------------------------------------------- : ConsolePanel

ConsolePanel::ConsolePanel(Window* parent, int id)
  : SetWindowPanel(parent, id)
  , menuConsole(nullptr)
  , messages(nullptr)
  , entry(nullptr)
  , is_active_window(false)
  , blinker_state(0)
  , blinker_timer(this)
{
  // init controls
  splitter = new wxSplitterWindow(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL);
  messages = new MessageCtrl(splitter, ID_MESSAGE_LIST);
  entry_panel = new wxPanel(splitter, wxID_ANY);
  entry = new HistoryTextCtrl(entry_panel, wxID_ANY);
  wxButton* evaluate = new wxButton(entry_panel, ID_EVALUATE, _BUTTON_("evaluate"));
  // init sizer for entry_panel
  wxSizer* se = new wxBoxSizer(wxHORIZONTAL);
  se->Add(entry,    1, wxEXPAND, 2);
  se->Add(evaluate, 0, wxEXPAND | wxLEFT, 2);
  entry_panel->SetSizer(se);
  // init splitter
  splitter->SetMinimumPaneSize(40);
  splitter->SetSashGravity(1.0);
  splitter->SplitHorizontally(messages, entry_panel, -50);
  // init sizer
  wxSizer* s = new wxBoxSizer(wxVERTICAL);
  s->Add(splitter, 1, wxEXPAND);
  s->SetSizeHints(this);
  SetSizer(s);

  // init menus
  menuConsole = new wxMenu();
  add_menu_item_tr(menuConsole, ID_CLEAR_CONSOLE, "clear_console", "clear console");
}

ConsolePanel::~ConsolePanel() {
  delete menuConsole;
}

void ConsolePanel::onChangeSet() {
  card = CardP();
}

void ConsolePanel::selectCard(const CardP& card) {
  this->card = card;
}

// ----------------------------------------------------------------------------- : UI

void ConsolePanel::initUI(wxToolBar* tb, wxMenuBar* mb) {
  // Menus
  // focus on entry
  entry->SetFocus();
  
  // stop blinker
  is_active_window = true;
  stop_blinker();

  add_tool_tr(tb, ID_CLEAR_CONSOLE, "clear_console", "clear console");
  tb->Realize();

  mb->Insert(2, menuConsole, _MENU_("console"));
}

void ConsolePanel::destroyUI(wxToolBar* tb, wxMenuBar* mb) {
  // Toolbar
  tb->DeleteTool(ID_CLEAR_CONSOLE);
  // Menus
  mb->Remove(2);

  // we are no longer active, allow blinker
  is_active_window = false;
}

void ConsolePanel::onUpdateUI(wxUpdateUIEvent& ev) {
  if (ev.GetId() == ID_EVALUATE) {
    ev.Enable(!entry->GetValue().empty());
  }
}

void ConsolePanel::onEnter(wxCommandEvent& ev) {
  onCommand(ID_EVALUATE);
}
void ConsolePanel::onCommand(int id) {
  if (id == ID_EVALUATE) {
    exec(entry->get_command_and_clear());
  }
  else if (id == ID_CLEAR_CONSOLE) {
    messages->clear_console();
  }
}

void ConsolePanel::onIdle(wxIdleEvent&) {
  get_pending_errors();
}

void ConsolePanel::get_pending_errors() {
  // The panel might not be initialized yet, in particular, construction of controls might fail, which results in a popup dialog with an event loop
  if (!messages) return;
  // add pending messages
  MessageType type;
  String msg;
  while (get_queued_message(type,msg)) {
    messages->add_message(type,msg);
    // If this panel doesn't have the focus, then highlight it somehow
    if (!is_active_window) {
      new_errors_since_last_view = max(new_errors_since_last_view,type);
      start_blinker();
    }
  }
}

void ConsolePanel::exec(String const& command) {
  if (command.empty()) return;
  // add input message
  messages->add_message(MESSAGE_INPUT, command);
  try {
    // parse command
    vector<ScriptParseError> errors;
    ScriptP script = parse(command,nullptr,false,errors);
    FOR_EACH(error,errors) {
      // TODO: also squiglify the input?
      messages->add_message(script ? MESSAGE_WARNING : MESSAGE_ERROR,error.what(), true);
    }
    if (!script) return;
    // execute command
    //WITH_DYNAMIC_ARG(export_info, &ei); // TODO: allow image export
    Context& ctx = set->getContext(card);
    ScriptValueP result = ctx.eval(*script,false);
    get_pending_errors();
    // show result
    ConsoleMessageP message = make_intrusive<ConsoleMessage>(MESSAGE_OUTPUT);
    message->joined_to_previous = true;
    message->value = result;
    // type of result
    ScriptType type = result->type();
    if (type == SCRIPT_IMAGE) {
      GeneratedImage::Options options(0,0, set->stylesheet.get(), set.get());
      wxImage image = result->toImage()->generate(options);
      message->bitmap = wxBitmap(image);
    } else if (type == SCRIPT_COLOR) {
      message->text = result->toCode();
      Color color = result->toColor();
      wxImage image(30,20);
      fill_image(image,color);
      set_alpha(image, color.Alpha() / 255.0);
      message->bitmap = wxBitmap(image);
    } else {
      message->text = result->toCode();
    }
    messages->add_message(message);
  } catch (ScriptError const& e) {
    messages->add_message(MESSAGE_ERROR, e.what(), true);
  }
}

BEGIN_EVENT_TABLE(ConsolePanel, wxPanel)
  EVT_TEXT_ENTER(wxID_ANY,ConsolePanel::onEnter)
  EVT_IDLE(ConsolePanel::onIdle)
  EVT_TIMER(wxID_ANY,ConsolePanel::onTimer)
END_EVENT_TABLE  ()

// ----------------------------------------------------------------------------- : Clipboard

// determine what control to use for clipboard actions
#define CUT_COPY_PASTE(op,return) \
  int id = focused_control(this); \
  if   (id == ID_MESSAGE_LIST) { return messages->op(); } \
  else                         { return false; }

bool ConsolePanel::canCut()   const { return false; }
bool ConsolePanel::canCopy()  const { CUT_COPY_PASTE(canCopy,  return) }
//void ConsolePanel::doCut()          { CUT_COPY_PASTE(doCut,    return (void)) }
void ConsolePanel::doCopy()         { CUT_COPY_PASTE(doCopy,   return (void)) }

// ----------------------------------------------------------------------------- : Annoying blinking icon thing

void ConsolePanel::start_blinker() {
  if (new_errors_since_last_view) {
    blinker_state = 0;
    update_blinker();
    if (blinker_state < MAX_BLINKS) {
      blinker_timer.Start(BLINK_TIME);
    }
  }
}
void ConsolePanel::stop_blinker() {
  blinker_state = 0;
  new_errors_since_last_view = MESSAGE_NONE;
  blinker_timer.Stop();
  update_blinker();
}
void ConsolePanel::onTimer(wxTimerEvent&) {
  blinker_state++;
  if (blinker_state >= MAX_BLINKS) {
    blinker_timer.Stop();
  }
  update_blinker();
}
void ConsolePanel::update_blinker() {
  SetWindow* parent = static_cast<SetWindow*>(GetParent());
  if (blinker_state % 2 == 1 || !new_errors_since_last_view) {
    parent->setPanelIcon(this, load_resource_image(_("tool/window_console")));
  } else if (new_errors_since_last_view == MESSAGE_INFO) {
    parent->setPanelIcon(this, load_resource_image(_("message_information")));
  } else if (new_errors_since_last_view == MESSAGE_WARNING) {
    parent->setPanelIcon(this, load_resource_image(_("message_warning")));
  } else {
    parent->setPanelIcon(this, load_resource_image(_("message_error")));
  }
}
