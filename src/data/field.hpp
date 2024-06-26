//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) Twan van Laarhoven and the other MSE developers          |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#pragma once

// ----------------------------------------------------------------------------- : Includes

#include <util/prec.hpp>
#include <util/reflect.hpp>
#include <util/alignment.hpp>
#include <util/age.hpp>
#include <util/rotation.hpp>
#include <data/localized_string.hpp>
#include <script/scriptable.hpp>
#include <script/dependency.hpp>
#include <script/image.hpp>

DECLARE_POINTER_TYPE(Field);
DECLARE_POINTER_TYPE(Style);
DECLARE_POINTER_TYPE(Value);
class Context;
class Dependency;
class Action;
class StyleListener;

// for DataViewer/editor
class DataViewer; class DataEditor;
DECLARE_POINTER_TYPE(ValueViewer);
DECLARE_POINTER_TYPE(ValueEditor);

// Value for which script updates are being run
DECLARE_DYNAMIC_ARG(Value*, value_being_updated);

// ----------------------------------------------------------------------------- : Field

/// Information on how to store a value
class Field : public IntrusivePtrVirtualBase, public IntrusiveFromThis<Field> {
public:
  Field();
  virtual ~Field();
  
  size_t    index;            ///< Used by IndexMap
  String    name;             ///< Name of the field, for refering to it from scripts and files
  LocalizedString caption;    ///< Caption for NativeLookEditor
  LocalizedString description;///< Description, used in status bar
  String    icon_filename;    ///< Filename for an icon (for list of fields)
  bool      editable;         ///< Can values of this field be edited?
  bool      save_value;       ///< Should values of this field be written to files? Can be false for script generated fields.
  bool      show_statistics;  ///< Should this field appear as a group by choice in the statistics panel?
  int       position_hint;    ///< Position in the statistics list
  bool      identifying;      ///< Does this field give Card::identification()?
  int       card_list_column; ///< What column to use in the card list?
  UInt      card_list_width;  ///< Width of the card list column (pixels).
  bool      card_list_visible;///< Is this field shown in the card list?
  bool      card_list_allow;  ///< Is this field allowed to appear in the card list?
  LocalizedString  card_list_name; ///< Name to use in card list.
  Alignment card_list_align;  ///< Alignment of the card list colummn.
  OptionalScript sort_script; ///< The script to use when sorting this, if not the value.
  Dependencies dependent_scripts; ///< Scripts that depend on values of this field
  String package_relative_filename;
  
  /// Creates a new Value corresponding to this Field
  virtual ValueP newValue() = 0;
  /// Creates a new Style corresponding to this Field
  virtual StyleP newStyle() = 0;
  /// Type of this field
  virtual String typeName() const = 0;
  
  /// Add the given dependency to the dependet_scripts list for the variables this field depends on
  virtual void initDependencies(Context& ctx, const Dependency& dep) const;
  
private:
  DECLARE_REFLECTION_VIRTUAL();
  virtual void after_reading(Version ver);
  friend void after_reading(Field& s, Version ver);
};

template <>
intrusive_ptr<Field> read_new<Field>(Reader& reader);
inline void update_index(FieldP& f, size_t index) {
  f->index = index;
}

inline void after_reading(Field& f, Version ver) {
  f.after_reading(ver);
}

inline String type_name(const Field&) {
  return _TYPE_("field");
}

// ----------------------------------------------------------------------------- : Style

/// Style information needed to display a Value in a Field.
class Style : public IntrusivePtrVirtualBase, public IntrusiveFromThis<Style> {
public:
  Style(const FieldP&);
  virtual ~Style();
  
  const FieldP       fieldP;          ///< Field this style is for, should have the right type!
  
  int                z_index;         ///< Stacking of values of this field, higher = on top
  int                tab_index;       ///< Tab index in editor
  Scriptable<double> left,  top;      ///< Position of this field
  Scriptable<double> width, height;   ///< Position of this field
  Scriptable<double> right, bottom;   ///< Position of this field
  Scriptable<Degrees> angle;          ///< Rotation of the box
  Scriptable<bool>   visible;         ///< Is this field visible?
  CachedScriptableMask mask;          ///< Mask image
  
  enum AutomaticSide {
    AUTO_UNKNOWN = 0x00,
    AUTO_LEFT    = 0x01, AUTO_WIDTH  = 0x02, AUTO_RIGHT  = 0x04, AUTO_LR = 0x08,
    AUTO_TOP     = 0x10, AUTO_HEIGHT = 0x20, AUTO_BOTTOM = 0x40, AUTO_TB = 0x80,
    ATTACH_LEFT  = 0x04, ATTACH_CENTER = 0x02, ATTACH_RIGHT  = 0x01,
    ATTACH_TOP   = 0x40, ATTACH_MIDDLE = 0x20, ATTACH_BOTTOM = 0x10,
  } automatic_side : 8;  ///< Which of (left, width,  right) and (top,  height, bottom) is determined automatically?
  bool content_dependent;  ///< Does this style depend on content properties?
  
  inline RealPoint getPos()  const { return RealPoint(left, top); }
  inline RealSize  getSize() const { return RealSize(width, height); }
  inline RealRect  getExternalRect() const { return RealRect(left, top, width, height); }
  
  /// Does this style have a non-zero size (or is it scripted)?
  bool hasSize() const;
  
  /// Get a copy of this style
  virtual StyleP clone() const = 0;
  
  /// Make a viewer object for values using this style
  virtual ValueViewerP makeViewer(DataViewer& parent) = 0;
  /// Make an editor object for values using this style
  virtual ValueViewerP makeEditor(DataEditor& parent) = 0;
  
  /// Update scripted values of this style, return nonzero if anything has changed.
  /** The caller should tellListeners()
   *  The result is a combination of StyleChange flags
   */
  virtual int update(Context&);
  /// Add the given dependency to the dependent_scripts list for the variables this style depends on
  /** Only use for things that need invalidate() */
  virtual void initDependencies(Context&, const Dependency&) const;
  /// Check if the style depends on content properties
  /** If there is such a dependency, set dep.index to true.
   *  This is done by mark_dependency_member for those properies */
  virtual void checkContentDependencies(Context&, const Dependency&) const;
  /// Dependencies on properies?
  /** In particular, if dep == DEP_DUMMY and name is a content property, set dep.index=true */
  virtual void markDependencyMember(const String& name, const Dependency&) const;
  /// Invalidate scripted images for this style
  virtual void invalidate() {}
  
  /// Add a StyleListener
  void addListener(StyleListener*);
  /// Remove a StyleListener
  void removeListener(StyleListener*);
  /// Tell the StyleListeners that this style has changed
  /** change_info is a subset of StyleChange flags */
  void tellListeners(int changes);
  
private:
  DECLARE_REFLECTION_VIRTUAL();
  /// Things that are listening to changes in this style
  vector<StyleListener*> listeners;
};

/// What changed in a style update?
enum StyleChange
{  CHANGE_NONE              = 0x00 // nothing changed
,  CHANGE_OTHER             = 0x01 // some other change (note: result of casting from bool)
,  CHANGE_SIZE              = 0x02 // size/angle changed
,  CHANGE_DEFAULT           = 0x04 // only the 'default' state is affected
,  CHANGE_MASK              = 0x08 // a mask image changed, must be reloaded
,  CHANGE_ALREADY_PREPARED  = 0x80 // hint that the change was the result of a content property change, viewers are already prepared
};

void init_object(const FieldP&, StyleP&);
inline const FieldP& get_key     (const StyleP& s) { return s->fieldP; }
inline const String& get_key_name(const StyleP& s) { return s->fieldP->name; }
template <> StyleP read_new<Style>(Reader&);

inline String type_name(const Style&) {
  return _TYPE_("style");
}

void mark_dependency_member(const Style& style, const String& name, const Dependency& dep);

// ----------------------------------------------------------------------------- : StyleListener

/// An object that can respond when a style changes;
class StyleListener : public IntrusivePtrVirtualBase {
public:
  StyleListener(const StyleP& style);
  virtual ~StyleListener();
  
  /// Called when a (scripted) property of the viewed style has changed
  /** changes is a combination of StyleChange flags */
  virtual void onStyleChange(int changes) {}
protected:
  const StyleP styleP; ///< The style we are listening to
};

// ----------------------------------------------------------------------------- : Value

/// A specific value 'in' a Field.
class Value : public IntrusivePtrVirtualBase {
public:
  inline Value(const FieldP& field) : fieldP(field) {}
  virtual ~Value();

  const FieldP fieldP;        ///< Field this value is for, should have the right type!
  Age          last_script_update;  ///< When where the scripts last updated? (by calling update)
  String       sort_value;      ///< How this should be sorted.

  /// Get a copy of this value
  virtual ValueP clone() const = 0;

  /// Convert this value to a string for use in tables
  virtual String toString() const = 0;
  /// Apply scripts to this value, return true if the value has changed
  virtual bool update(Context& ctx);
  /// This value has been updated by an action
  /** Does nothing for most Values, only FakeValues can update underlying data */
  virtual void onAction(Action& a, bool undone) {}
  /// Is this value the same as some other value (for the same field&card)
  /** Has behaviour other than == for FakeTextValue.
   *  In that case returns true if this and that editing the same undelying value.
   *  If so, this value is updated to reflect the (possibly changed) underlying value.
   */
  virtual bool equals(const Value* that);

  /// Get the key to use for sorting this value
  inline String getSortKey() const {
    return fieldP->sort_script ? sort_value : toString();
  }

protected:
  /// update() split into two functions;.
  /** Derived classes should put their stuff in between if they need the age in scripts */
  void updateAge();
  void updateSortValue(Context& ctx);

private:
  DECLARE_REFLECTION_VIRTUAL();
};

void init_object(const FieldP&, ValueP&);
inline const FieldP& get_key     (const ValueP& v) { return v->fieldP; }
inline const String& get_key_name(const ValueP& v) { return v->fieldP->name; }
template <> ValueP read_new<Value>(Reader&);

inline String type_name(const Value&) {
  return _TYPE_("value");
}

// ----------------------------------------------------------------------------- : Utilities

#define DECLARE_FIELD_TYPE(Type) \
    DECLARE_REFLECTION_OVERRIDE(); \
  public: \
    virtual ValueP newValue() override; \
    virtual StyleP newStyle() override; \
    virtual String typeName() const override

// implement newStyle and newValue
#define IMPLEMENT_FIELD_TYPE(Type, NAME) \
  StyleP Type ## Field::newStyle() { \
    return make_intrusive<Type ## Style>(static_pointer_cast<Type ## Field>(intrusive_from_this())); \
  } \
  ValueP Type ## Field::newValue() { \
    return make_intrusive<Type ## Value>(static_pointer_cast<Type ## Field>(intrusive_from_this())); \
  } \
  StyleP Type ## Style::clone() const { \
    return make_intrusive<Type ## Style>(*this); \
  } \
  ValueP Type ## Value::clone() const { \
    return make_intrusive<Type ## Value>(*this); \
  } \
  String Type ## Field::typeName() const { \
    return _(NAME); \
  }

#define DECLARE_STYLE_TYPE(Type) \
    DECLARE_REFLECTION_OVERRIDE(); \
  public: \
    DECLARE_HAS_FIELD(Type) \
    StyleP clone() const override; \
    ValueViewerP makeViewer(DataViewer& parent) override; \
    ValueViewerP makeEditor(DataEditor& parent) override

#define DECLARE_VALUE_TYPE(Type,ValueType_) \
    DECLARE_REFLECTION_OVERRIDE(); \
  public: \
    DECLARE_HAS_FIELD(Type) \
    ValueP clone() const override; \
    String toString() const override; \
    typedef ValueType_ ValueType

// implement field() which returns a field with the right (derived) type
#define DECLARE_HAS_FIELD(Type) \
  inline Type ## Field& field() const { \
    return *static_cast<Type ## Field*>(fieldP.get()); \
  }

void mark_dependency_member(const IndexMap<FieldP,ValueP>& value, const String& name, const Dependency& dep);

