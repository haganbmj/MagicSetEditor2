Data Types
============

Magic Set Editor uses many data types in the files and in scripting.
There are for instance :ref:`card`s in :ref:`set`s, :ref:`stylesheet`s describing the layout of :ref:`field`s, etc.

1. :doc:`set <#set>`
2. :ref:`set`
3. :ref:`sets <set>`


File Types
----------

These are the 'major' data types that are written directly to :doc:`/file/packages`.

.. list-table:: 
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - :ref:`game`
      - What information is on each card?
    * - :ref:`stylesheet`
      - What do cards look like?
    * - :ref:`set`
      - Sets of cards.
    * - :ref:`symbol font`
      - Fonts consisting of symbols, for instance mana symbols.
    * - :ref:`export template`
      - How to export sets to HTML files?
    * - :ref:`locale`
      - Translations of MSE.
    * - :ref:`include`
      - Files to include in other templates.
    * - :ref:`installer`
      - Installers containing several packages.
    * - :ref:`symbol`
      - Expansion symbols.
    * - :ref:`settings`
      - MSE settings.

Game
~~~~

**Overview**

Games are part of the :doc:`/concepts#style-triangle`:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 0
    :align: left

    * - Description	
      - Looks
      - Data
    * - **:ref:`Game`**
      - :ref:`Stylesheet`
      - :ref:`Set`
    * - :ref:`Field`
      - :ref:`Style`	
      - :ref:`Value`

Games provide the ''description'', i.e. what kinds of things are on a card.

**Package format**

A game is described in a :doc:`/file/package` with the ``.mse-game`` file extension.
Such a package contains a :doc:`/file/format|data file` called ``game`` that has the following properties.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - '''Common to all packages'''
      - <<<
      - <<<
      - <<<
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this game is made for.
    * - ``short name``	
      - :ref:`string`	
      - file name
      - A short name of this game, for the 'new set' list.
    * - ``full name``	
      - :ref:`string`	
      - file name
      - A longer name of this game.
    * - ``icon``	
      - :ref:`filename`
      - ''none''
      - Filename of an icon / preview for this game, for the 'new set' list.
    * - ``position hint``
      - :ref:`int`	
      - &infin;	
      - Where to place this item in the 'new set' list? Lower numbers come first.
    * - ``version``	
      - :ref:`version`
      - ``0.0.0``	
      - Version number of this package.
    * - ``depends on``	
      - | :ref:`list` of :ref:`dependency`s
        | Packages this package depends on.
    * - '''Specific to games'''	
      - <<<
      - <<<
      - <<<
    * - ``init script``
      - :ref:`script`	
      - ``;``	
      - | Script to run when this game is loaded,<br/> can set variables
        | to be used by other scripts in this game or stylesheets using it.
    * - ``set fields``
      - :ref:`list` of :ref:`field`s
      -  	
      - Fields for the styling panel.
    * - ``default set style``	
      - :ref:`indexmap` of :ref:`style`s
      -  	
      - Default style for the set fields, can be overridden by the stylesheet.
    * - ``card fields``
      - :ref:`list` of :ref:`field`s
      -  	
      - Fields for each card.
    * - ``card list color script``
      - :ref:`script`	
      - from fields
      - Script that determines the color of an item in the card list. <br/>If not set uses the ``card list colors`` property of the first card field that has it.
    * - ``statistics dimensions``
      - :ref:`list` of :ref:`statistics dimension`s	
      - from fields
      - Dimensions for statistics, a dimension is roughly the same as an axis. <br/>By default all card fields with 'show statistics' set to true are used.
    * - ``statistics categories``
      - :ref:`list` of :ref:`statistics category`s	
      - from dimensions
      - | DOC_MSE_VERSION: not used since 0.3.6
        | Choices shown on the statistics panel. <br/>By default all statistics dimensions are used.
    * - ``pack types``
      - :ref:`list` of :ref:`pack type`s
      -  	
      - | DOC_MSE_VERSION: since 0.3.7
        | The types of card packs that will be listed on the random booster panel.
    * - ``has keywords``	
      - :ref:`boolean`
      - ``false``	
      - Does this game use keywords? Should the keywords tab be available?
    * - ``keyword match script``
      - :ref:`script`	
      - ``;``	
      - Script to apply to the ``match`` property of keywords.
    * - ``keyword modes``	
      - :ref:`list` of :ref:`keyword mode`s	
      -  
      - Choices for the 'mode' property of keywords.
    * - ``keyword parameter types``
      - :ref:`list` of :ref:`keyword param type`s
      -  
      - Types of parameters available to keywords.
    * - ``keywords``
      - :ref:`list` of :ref:`keyword`s	
      -  
      - Standard keywords for this game.
    * - ``word lists``
      - :ref:`list` of :ref:`word list`s
      -  	
      - Word lists that can be used by text fields.
    * - ``add cards script``	
      - :ref:`list` of :ref:`add cards script`s
      -  
      - | DOC_MSE_VERSION: since 0.3.7
        | A list of scripts for conveniently adding multiple cards to a set.

**Examples**
Look at the game files in the standard MSE distribution for examples.

Stylesheet
~~~~~~~~~~

**Overview**

Stylesheets are part of the :doc:`/file/style triangle`:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 0
    :align: left

    * - Description	
      - Looks
      - Data
    * - :ref:`Game`	
      - **:ref:`Stylesheet`**
      - :ref:`Set`
    * - :ref:`Field`
      - :ref:`Style`	
      - :ref:`Value`

Stylesheets provide the ''look and feel'' of cards.

**Package format**
A stylesheet is described in a :doc:`/file/package` with the ``.mse-style`` file extension,
such a package contains a data file called ``style``.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - '''Common to all packages'''
      - <<<
      - <<<
      - <<<
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this stylesheet is made for.
    * - ``short name``	
      - :ref:`string`	
      - file name
      - A short name of this stylesheet, for the 'new set' and style panel lists.
    * - ``full name``	
      - :ref:`string`	
      - file name
      - A longer name of this stylesheet.
    * - ``icon``	
      - :ref:`filename`
      - ''none''
      - Filename of an icon / preview for this stylesheet, for the 'new set' and style panel lists.
    * - ``position hint``
      - :ref:`int`	
      - &infin;	
      - Where to place this item in the list? Lower numbers come first.
    * - ``version``	
      - :ref:`version`
      - ``0.0.0``	
      - Version number of this package.
    * - ``depends on``	
      - | :ref:`list` of :ref:`dependency`s
        | Packages this package depends on.
    * - '''Specific to stylesheets'''	
      - <<<
      - <<<
      - <<<
    * - ``game``	
      - Name of a :ref:`game`
      - ''required''
      - Game this stylesheet is made for
    * - ``card width``	
      - :ref:`double`	
      - 100	
      - Width of cards in pixels
    * - ``card height``	
      - :ref:`double`	
      - 100	
      - Height of cards in pixels
    * - ``card dpi``	
      - :ref:`double`	
      - 96	
      - Resolution of cards in dots-per-inch
    * - ``card background``
      - :ref:`color`	
      - white	
      - Background color of cards
    * - ``init script``	
      - :ref:`script`	
      - ``;``	
      - Script to run when this stylesheet is loaded, after the game's init script.
    * - ``styling fields``
      - :ref:`list` of :ref:`field`s
      -  	
      - Fields for styling options, shown on the 'style' panel.
    * - ``styling style``
      - :ref:`indexmap` of :ref:`style`s
      -  	
      - Styles for the styling fields.
    * - ``set info style``
      - :ref:`indexmap` of :ref:`style`s
      - game.default_set_style
      - Styling for the 'set info' panel
    * - ``card style``	
      - :ref:`indexmap` of :ref:`style`s
      -  	
      - Styles for the card fields defined in the game
    * - ``extra card fields``
      - :ref:`list` of :ref:`field`s
      -  	
      - | Additional fields to add to each card.<br/>
        | These fields are intended for things like lines and boxes, whose value is determined automatically.
    * - ``extra card style``
      - :ref:`indexmap`` of :ref:`style`s
      -  	
      - Styling for the extra card fields

Set
~~~

**Overview**

Sets are part of the :doc:`/file/style triangle`:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 0
    :align: left

    * - Description	
      - Looks
      - Data
    * - :ref:`Game`	
      - :ref:`Stylesheet`
      - **:ref:`Set`**
    * - :ref:`Field`
      - :ref:`Style`	
      - :ref:`Value`

**Package format**
A set is described in a :doc:`/file/package` with the ``.mse-set`` file extension,
such a package contains a data file called ``set``.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - '''Common to all packages'''
      - <<<
      - <<<
      - <<<
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this set is made with.
    * - ``short name``	
      - :ref:`string`	
      - file name
      - Name of this set.
    * - ``depends on``	
      - | :ref:`list` of :ref:`dependency`s
        | Packages this package depends on.
    * - '''Specific to sets'''	
      - <<<
      - <<<
      - <<<
    * - ``game``
      - Name of a :ref:`game`
      - ''required''
      - The game this set is made for.
    * - ``stylesheet``
      - Name of a :ref:`stylesheet`	
      - ''required''
      - | The default style for drawing cards in this set.<br/>
        | This is without the game name or extension, so ``"new"`` refers to the package ``"gamename-new.mse-style"``.
    * - ``set info``
      - :ref:`indexmap` of :ref:`value`s
      -  
      - The data for the [[prop:game:set fields` defined in the game.
    * - ``styling``
      - | :ref:`map` of :ref:`indexmap`s of :ref:`value`s
        | Data for the 'extra fields' of the stylesheet.<br/>
        | This is first indexed by stylesheet name, then by field name.<br/>
        | Data is given not only for the set's stylesheet but also for those of cards.
    * - ``cards``
      - :ref:`list] of :ref:`card`s	
      -  
      - The cards in the set.
    * - ``keywords``
      - :ref:`list] of :ref:`keyword`s
      -  
      - The custom keywords in the set.
    * - ``pack types``
      - :ref:`list` of :ref:`pack type`s
      -  
      - | DOC_MSE_VERSION: since 0.3.8
        | The custom card pack types in the set.

**Example**

If the game looks like:

.. code-block::

    mse version: 0.3.4
    name: my game
    set field:
    	name: copyright
    	type: text
    card field:
    	name: card name
    	type: text
    card field:
    	name: power
    	type: text

The the a set file would looks like:

.. code-block::

    mse version: 0.3.4
    game: my game
    name: my set
    set info:
    	copyright: something
    extra set info:
    	name of style:
    		name of field: something
    card:
    	card name: first card
    	power: 100
    card:
    	card name: second card
    	power: 50

Pack Type
~~~~~~~~~

DOC_MSE_VERSION: since 0.3.8

**Overview**

A type of card packs. For instance "booster" and "tournament pack" are card pack types.

A pack type contains either:
* a filter for selecting the desired kind of cards from the set.
* one or more :ref:`pack item`s, indicating what kinds and how many cards are in the pack.
* a combination of the above.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type
      - Default	
      - Description
    * - ``name``
      - :ref:`string`	
      -  	
      - | Name of this card pack type.
        | Other pack types can refer to this name.
    * - ``select``
      - see below	
      - see below
      - How are instances of this pack generated?
    * - ``enabled``
      - :ref:`scriptable` :ref:`boolean`
      - ``true``	
      - Is this pack type enabled, i.e. can the user select it?
    * - ``selectable``
      - :ref:`boolean`
      - ``true``	
      - Is this pack selectable from the list of packs in the user interface?
    * - ``summary``
      - :ref:`boolean`
      - ``true``	
      - | Is a summary of the total number of cards shown in the second panel in the user interface?<br/>
        | Note: this only applies to pack types that have the ``filter`` property set.
    * - ``filter``
      - :ref:`script`	
      - ''optional''
      - Condition that a card must satisfy to be included in this pack type.
    * - ``items``
      - :ref:`list` of :ref:`pack item`s
      -  	
      - The items to include in this pack.

**Selection**

The ``select`` property specifies how instances of this pack are generated.
When the user selects that he wants 3 copies of pack X, then MSE will generate three ''instances'' of that pack.
How that happens depends on the ``select`` property:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - ``select``	
      - Description
    * - ``all``
      - | Each instance of this pack type contains all of the filtered cards and ``items``.<br/>
        | In general, ``select: all`` is used for the selectable pack types, while other ``select`` types are used for the rest of the packs.<br/>
        | This is the default for pack types with ``items``.
    * - ``replace``	
      - | Each instance of this pack type contains a single card or ``item``, chosen at random with replacement.
        | The probability of picking an item is proportional to its ``weight``, all filtered cards have weight 1.
    * - ``no replace``	
      - | Each instance of this pack type contains a single card or ``item``, chosen at random without replacement.
        | This means that the same card or item will not be chosen twice (if the set is large enough).<br/>
        | This is the default for pack types with a ``filter``.
    * - ``proportional``
      - | Each instance of this pack type contains a single filtered card or ``item``, chosen with probability proportional to the number of choices for the card/item.
        | The choice is made with replacement.
    * - ``nonempty``	
      - | Each instance of this pack type contains a single filtered card or ``item``,
        | but items that contain no cards will be ignored.
        | The choice is made with replacement.
    * - ``equal``	
      - Instead of choosing cards and items at random, they are chosen to make their numbers as equal as possible.
    * - ``equal proportional``
      - A combination of ``equal`` and ``proportional``.
    * - ``equal nonempty``
      - A combination of ``equal`` and ``nonempty``.
    * - ``first``	
      - | If there are any cards, the first is always chosen, otherwise the first ''nonempty'' item is used.<br/>
        | ``select: first`` can be used to make a kind of if statement: "If there are any X cards then use those, otherwise use Y cards".

**Examples**

.. code-block::

    pack item:
    	name: rare
    	select: no replace # this is optional, 'no replace' is the default
    	filter: card.rarity == "rare"

Rare cards are those with the rarity value of ``"rare"``.
The cards are chosen without replacement, so in a single pack the same rare will not occur twice.


.. code-block::

    pack item:
    	name: basic land
    	select: equal
    	filter: card.rarity == "basic land"

Basic land cards are selected in equal amounts:
Say a set contains two basic lands: "Good Land" and "Bad Land".
Then if 6 basic lands are selected, there will always be exactly 3 "Good Lands" and 3 "Bad Lands".
If an odd number of basic lands are selected then the amounts will be as close as possible to being equal.



.. code-block::

    pack type:
    	name: booster pack
    	select: all # this is optional, 'all' is the default
    	item:
    		name: rare
    		amount: 1
    	item:
    		name: uncommon
    		amount: 3
    	item:
    		name: common
    		amount: 11

A Magic booster pack contains 1 rare, 3 uncommons and 11 commons.


.. code-block::

    pack type:
    	name: special or else common
    	select: first
    	item: special
    	item: common

If there are any special cards in the set, then "special or else common" will be a special card, otherwise it will be a common.


.. code-block::

    pack type:
    	name: rare or mythic rare
    	select: proportional
    	item:
    		name: rare
    		weight: 2
    	item:
    		name: mythic rare
    		weight: 1

In Magic, individual "mythic rares" are twice as rare as normal rare cards.
Since there are also less mythic rares, this does not mean that each booster pack has a 33% percent chance of containing a mythic rare.
Instead the probability of a mythic rare is
``number_of_mythics / (number_of_rares * 2 + number_of_mythics)``.
So, for example if there are 20 rares in a set and only 5 mythic rares, then one in 9 "rare or mythic rare" cards will be a mythic rare.

Pack Item
_________

DOC_MSE_VERSION: since 0.3.8

**Overview**

A reference to another :ref:`pack type`, from which one or more cards are chosen.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type	
      - Default	
      - Description
    * - ``name``
      - Name of a :ref:`pack item`
      - ''required''
      - Name of the pack item to include in this pack.
    * - ``amount``
      - :ref:`scriptable` :ref:`int`
      - 1
      - How many of those cards are in the pack?
    * - ``weight``
      - :ref:`scriptable` :ref:`double`
      - 1
      - | How 'important' is this item?
        | Items with a higher weight will be chosen more often.
        | Cards from ``filter`` will have a weight of 1.

**Examples**

.. code-block::

    item:
    	name: common
    	amount: 11

Include 11 commons in this :ref:`pack type|pack`.


.. code-block::

    item: common
Short form. Include a single common in this pack.


Symbol Font
~~~~~~~~~~~

**Overview**

A symbol font is a font for drawing with images.
Each :ref:`symbol font symbol|symbol-font-symbol` in the font is an image.

A symbol font is referenced in :ref:`stylesheet`s using a :ref:`symbol font reference`.

**Splitting**

A piece of text drawn with the symbol font is split into separate symbols.
The list of symbols in the font is scanned from top to bottom to find matches.

If the text is for instance "W/GR" and "W/G" should be rendered as a single symbol, then it should appear before the symbol "W".
Otherwise the "W" is seen as a symbol and the program continues with rendering "/GR".

**Font size**

A symbol font is drawn using a specific point size, similar to normal fonts.
Usually the images that make up the font are given in a very high resolution, for example 200x200.
This resolution could correspond to a point size of for instance 150pt.

When the symbol is drawn at for instance 12pt the image well then be scaled down to ``200/150*12 == 16`` pixels.

Sizes like margin, padding and font size are given in 'pixels per point'. If for instance

.. code-block::

     text margin left: 0.1
is specified, and the symbol is rendered at 12pt, the margin will be ``12*0.1 == 1.2`` pixels.

**Package format**

A symbol font is described in a :doc:`/file/package` with the ``.mse-symbol-font`` file extension.
Such a package contains a :doc:`/file/format|data file` called ``symbol-font`` that has the following properties.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - '''Common to all packages'''
      - <<<
      - <<<
      - <<<
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this symbol font is made for.
    * - ``short name``	
      - :ref:`string`	
      - file name
      - A short name of this symbol font, currently not used by the program.
    * - ``full name``	
      - :ref:`string`	
      - file name
      - A longer name of this symbol font, currently not used by the program.
    * - ``icon``	
      - :ref:`filename`
      - ''none''
      - Filename of an icon, currently not used by the program.
    * - ``version``	
      - :ref:`version`
      - ``0.0.0``	
      - Version number of this package.
    * - ``depends on``	
      - | :ref:`list` of :ref:`dependency`s
        | Packages this package depends on.
    * - '''Specific to symbol fonts'''	
      - <<<
      - <<<
      - <<<
    * - ``image font size``	
      - :ref:`double`
      - ``12``	
      - To what point size do the images correspond?
    * - ``horizontal space``	
      - :ref:`double`
      - ``0``	
      - Horizontal spacing between symbols, in pixels.
    * - ``vertical space``	
      - :ref:`double`
      - ``0``	
      - Vertical spacing between symbols, in pixels.
    * - ``symbols``
      - :ref:`list` of :ref:`symbol font symbol`s
      -  
      - Symbols that make up this font.
    * - ``scale text``
      - :ref:`boolean`	
      - ``false``	
      - Should text be scaled down to fit in a symbol?
    * - ``insert symbol menu``	
      - :ref:`insert symbol menu|"insert symbol" menu`
      - ''none''
      - A description of the menu to insert a symbol into the text.

**Examples**
See for instance the ``"magic-mana-small.mse-symbol-font"`` package in the MSE distribution.

Symbol Font Reference
_____________________

**Overview**

A reference to a :ref:`symbol font`.

In :ref:`stylesheet`s the symbol fonts are not included inline, instead they are referenced by their package name.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - ``name``	
      - | :ref:`scriptable` Name of a :ref:`symbol font`
        | ''required''		Name of the symbol font package to use (without the extension).
    * - ``size``	
      - :ref:`scriptable` :ref:`double`
      - 12
      - Size in points to render the symbols with.
    * - ``scale down to``
      - :ref:`double`	
      - 1
      - Minimum size in points to scale the size down to.
    * - ``alignment``	
      - :ref:`scriptable` :ref:`alignment`
      - ``"middle center"``
      - Alignment of symbols in a line of text.

**Example**

.. code-block::

    symbol font:
    	name: magic-mana-small
    	size: 10
    	alignment: top left
The name can be scripted:

.. code-block::

    symbol font:
    	name: { if set.use_larga_mana_symbols then "magic-mana-large" else "magic-mana-small" }
    	size: 10
    	alignment: top left

Symbol Font Symbol
__________________

**Overview**

A single symbol in a :ref:`symbol font`.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - ``image font size``
      - :ref:`double`	
      - value from symbol font
      - To what point size does the images correspond?
    * - ``code``	
      - :ref:`string` or :ref:`regex`
      - ''required''	
      - Text this symbol matches.
    * - ``regex``	
      - :ref:`boolean`
      - ``false``
      - Is the code a regular expression (as opposed to a string)?
    * - ``image``	
      - :ref:`scriptable` :ref:`image`
      - ''required''	
      - Image of this symbol.
    * - ``enabled``	
      - :ref:`scriptable` :ref:`boolean`
      - ``true``
      - | Is this symbol actually used?<br/>
        | This can be scripted to optionally disable certain symbols.<br/>
        | If multiple symbols with the same code are given disabling the first switches to the second one.
    * - ``draw text``
      - :ref:`int`
      - ``-1``
      - The index of the captured regex expression to draw as text, or -1 to not draw text.<br/> For example with the code ``"x([a-z])"`` and ``draw text: 1`` the text of the symbol ``"xb"`` will be ``"b"``.
    * - ``text font``
      - :ref:`font`
      -  
      - Font to use for drawing text on symbols. The font size is in font points per text box font point.
    * - ``text alignment``	
      - :ref:`alignment`	
      - ``"middle center"``
      - How should text be aligned on the symbol?
    * - ``text margin left``	
      - :ref:`double`
      - ``0``
      - Margin on the left   of the text in pixels per point.
    * - ``text margin right``	
      - :ref:`double`
      - ``0``
      - Margin on the right  of the text in pixels per point.
    * - ``text margin top``	
      - :ref:`double`
      - ``0``
      - Margin on the top    of the text in pixels per point.
    * - ``text margin bottom``	
      - :ref:`double`
      - ``0``
      - Margin on the bottom of the text in pixels per point.


**Examples**
A symbol with text:

.. code-block::

    symbol:
    	image: blank.png
    	code:  .
    	regex: true
    	text font: Arial

Two symbols for the same code, which one is used depends on a function from the :ref:`stylesheet`.
It is recommended to only use functions in ``enabled``, so each stylesheet can determine how the font should be used.

.. code-block::

    symbol:
    	code: T
    	image: mana_t_old.png
    	enabled: { use_old_tap_symbol() }
    symbol:
    	code: T
    	image: mana_t.png


Insert Symbol Menu
__________________

**Overview**

A description of the "Insert symbol" menu for a specific :ref:`symbol font`.

The menu consists of a number of entries, either items, separators or submenus.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type
      - Default	
      - Description
    * - ``type``
      - One of:
      - ``"code"`` or ``"submenu"``	
      - What type of menu item is this?
		* ``code``, inserts a symbol with the given code.
		* ``custom``, pops up a dialog where the user can choose a code to insert.
		* ``line``, a separating line.
		* ``submenu``, a submenu.
    * - ``name``
      - :ref:`string`	
      - ''required''
      - Name of this menu item, corresponding to the code to insert.
    * - ``label``
      - :ref:`localized string`	
      - name
      - Label to show in the menu.
    * - ``prompt``
      - :ref:`localized string`	
      -  
      - Prompt to use for the pop up box with ``custom`` type
    * - ``items``
      - :ref:`list` of :ref:`insert symbol menu|submenu items`
      -  
      - Items in the submenu, when items are present the ``type`` is set to ``"submenu"``.

For custom items the dialog will be titled with the ``label`` and have message text ``prompt``.

**Examples**
A menu for magic mana symbols (simplified). Containing all types of items.

.. code-block::

    insert symbol menu:
    	item:
    		type: custom
    		name: Generic
    		prompt: How much generic mana?
    	item:
    		type: line
    	item: W
    	item: U
    	item: B
    	item: R
    	item: G
    	item:
    		label: Complex
    		name: cplx
    	item:
    		type: line
    	item:
    		name: hybrid
    		item: W/U
    		item: U/B
    		item: B/R
    		item: R/G
    		item: G/W


Export Template
~~~~~~~~~~~~~~~

**Overview**

An export template describes a way for a set to be exported to a HTML or other text files.

**Package format**
An export template is described in a :doc:`/file/package` with the ``.mse-export-template`` file extension.
Its name should begin with ``<i>game</i>-`` where <i>game</i> is the name of the game the template is made for.
It should contain a :doc:`/file/format|data file` called ``export-template`` with the following properties.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - '''Common to all packages'''
      - <<<
      - <<<
      - <<<
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this export template is made for.
    * - ``short name``	
      - :ref:`string`	
      - file name
      - A short name of this export template, for the 'new set' and style panel lists.
    * - ``full name``	
      - :ref:`string`	
      - file name
      - A longer name of this export template.
    * - ``icon``	
      - :ref:`filename`
      - ''none''
      - Filename of an icon / preview for this export template, for the 'export to HTML' dialog.
    * - ``position hint``
      - :ref:`int`	
      - &infin;	
      - Where to place this item in the list? Lower numbers come first.
    * - ``version``	
      - :ref:`version`
      - ``0.0.0``	
      - Version number of this package.
    * - ``depends on``	
      - | :ref:`list` of :ref:`dependency`s
        | Packages this package depends on.
    * - '''Specific to export template'''	
      - <<<
      - <<<
      - <<<
    * - ``game``	
      - Name of a :ref:`game`
      - ''required''
      - Game this export template is made for
    * - ``file type``	
      - :ref:`string`	
      - | ``"HTML files (*.html)|*.html"``
        | File type to use, this is a list separated by ``|`` characters.
        | Alternatingly, a human description and a file pattern to match are given.
    * - ``create directory``
      - :ref:`boolean`
      - ``false``	
      - Should a directory for data files be created? This is required for some script function.
    * - ``option fields``
      - :ref:`list` of :ref:`field`s
      -  
      - Fields for additional options to show.
    * - ``option style``
      - :ref:`indexmap` of :ref:`style`s
      -  
      - Styling for the ``option fields``.
    * - ``script``	
      - :ref:`script`	
      -  	
      - Script that generates the text that will be written to the exported file.

During the evaluation of the script the following variables are available:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - ``game``
      - The current game.
    * - ``style``
      - The current stylesheet.
    * - ``set``	
      - The set being exported.
    * - ``cards``
      - The cards selected by the user.
    * - ``options``
      - The values of the ``option fields``.
    * - ``directory``
      - Name of the directory created (if ``create directory`` is set).

**See also**
The following functions are made specifically for exporting to html:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :doc:`/function#to_html`	
      - Convert :ref:`tagged text` to html.
    * - :doc:`/function#symbols_to_html`
      - Convert text to html using a :ref:`symbol font`.
    * - :doc:`/function#to_text`	
      - Remove all tags from tagged text.
    * - :doc:`/function#copy_file`	
      - Copy a file from the :ref:`export template` to the output directory.
    * - :doc:`/function#write_text_file`
      - Write a text file to the output directory.
    * - :doc:`/function#write_image_file`
      - Write an image file to the output directory.

**Example**
Look at the ``"magic-spoiler.mse-export-template"`` for an example.

Locale
~~~~~~

**Overview**

A locale gives a translation of the user interface of the program.

**Package format**

A locale is described in a :doc:`/file/package` with the ``.mse-locale`` file extension.
Such a package contains a data file called ``locale`` that has the following properties.
There are usually no other files in the package.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - '''Common to all packages'''
      - <<<
      - <<<
      - <<<
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this locale is made for.
    * - ``short name``	
      - :ref:`string`	
      - file name
      - A short name of this locale, for the options dialog.
    * - ``full name``	
      - :ref:`string`	
      - file name
      - A longer name of this locale.
    * - ``icon``	
      - :ref:`filename`
      - ''none''
      - Filename of an icon / preview for this locale, currently not used.
    * - ``version``	
      - :ref:`version`
      - ``0.0.0``	
      - Version number of this package.
    * - '''Specific to locales'''	
      - <<<
      - <<<
      - <<<
    * - ``menu``	
      - :ref:`map` of :ref:`string`s
      -  
      - | Translations of menu items.<br/>
        | Menu items can contain shortcut keys (like Ctrl+C for copy) by using a ''single'' TAB between the text and the shortcut key.<br/>
        | Keys to use with Alt+Something (displayed underlined) can be specified &</br>
        | For example
        | >>>new set: &amp;New...&#9;Ctrl+N
    * - ``help``	
      - :ref:`map` of :ref:`string`s
      -  
      - Translations of help texts for the status bar.
    * - ``tool``	
      - :ref:`map` of :ref:`string`s
      -  
      - Translations of toolbar item texts.
    * - ``tooltip``	
      - :ref:`map` of :ref:`string`s
      -  
      - Translations of tooltips for toolbar items.
    * - ``label``	
      - :ref:`map` of :ref:`string`s
      -  
      - Labels of controls in the GUI.
    * - ``button``	
      - :ref:`map` of :ref:`string`s
      -  
      - Labels of buttons in the GUI.
    * - ``title``	
      - :ref:`map` of :ref:`string`s
      -  
      - Titles of windows.
    * - ``action``	
      - :ref:`map` of :ref:`string`s
      -  
      - Names of actions for undo/redo, things like "typing" and "add card".
    * - ``error``	
      - :ref:`map` of :ref:`string`s
      -  
      - Error messages.
    * - ``type``	
      - :ref:`map` of :ref:`string`s
      -  
      - Types of objects for error messages.
    * - ``game``	
      - | :ref:`map` of :ref:`map` of :ref:`string`s
        | Deprecated since MSE 2.1.3, use ``localized_...`` instead.<br/>
        | Translations for specific :ref:`game`s.<br/>
        | Field names and field descriptions are looked up in the locale, if they are found the translation is used, otherwise the value from the game file.<br/>
        | Extra keys not present in the English locale can be added here.
    * - ``stylesheet``	
      - | :ref:`map` of :ref:`map` of :ref:`string`s
        | Deprecated since MSE 2.1.3, use ``localized_...`` instead.<br/>
        | Translations for specific :ref:`stylesheet`s.
    * - ``symbol font``	
      - | :ref:`map` of :ref:`map` of :ref:`string`s
        | Deprecated since MSE 2.1.3, use ``localized_...`` instead.<br/>
        | Translations for specific :ref:`symbol font`s, in particular the "insert symbol" menu.

Some of the items can contain placeholders for other values, for example:

.. code-block::

     undo: &Undo%s	Ctrl+Z
The ``%s`` is replaced by the name of the action to undo.
This ``%s`` should be used in exactly those entries that also contain it in the English locale.

**Examples**
Look at the ``"en.mse-locale"`` file in the standard MSE distribution for an example.

**Translating MSE**
To translate the MSE user interface:
* Create a copy of the ``"en.mse-locale"`` directory, name it ``"**.mse-locale"``, where ``"**"`` is a two or three letter [[http://en.wikipedia.org/wiki/ISO_language_code|ISO language code`.
* Open the ``"locale"`` file with Notepad (or another program that supports UTF-8), and translate the strings.
* Add new keys for game, stylesheet or symbol font specific keys as described above.
* Save the file, select the new locale from Edit->Preferences.
* Restart MSE, and make sure everything looks right.
* Submit the new locale to the [[http://magicseteditor.sourceforge.net/forum/7|MSE forum].
* Maintain the locale when new versions of MSE come out. A new version may have new user interface items and therefore new keys.

Include
~~~~~~~

**Overview**

An include package contains files used by other packages, for example scripts or images.

**Package format**
An include package is described in a :doc:`/file/package` with the ``.mse-include`` file extension.
It should contain a :doc:`/file/format|data file` called ``include`` with the following properties.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default
      - Description
    * - '''Common to all packages'''
      - <<<
      - <<<
      - <<<
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this include package is made for.
    * - ``short name``	
      - :ref:`string`	
      - file name
      - A short name of this include package, currently not used.
    * - ``full name``	
      - :ref:`string`	
      - file name
      - A longer name of this include package, currently not used.
    * - ``icon``	
      - :ref:`filename`
      - ''none''
      - Filename of an icon / preview for this export template, currently not used.
    * - ``version``	
      - :ref:`version`
      - ``0.0.0``	
      - Version number of this package.
    * - ``depends on``	
      - | :ref:`list` of :ref:`dependency`s
        | Packages this package depends on.

No additional properties are available.

Installer
~~~~~~~~~

BLANK

Symbol
~~~~~~

**Overview**

A symbol file contains a symbol created with the symbol editor.

Symbols are not stored in packages, the data file is directly written to a ``".mse-symbol"`` file.

**Coordinates**

Various parts of a symbol use :ref:`vector2d|coordinates`.
These are pairs of numbers in the range ``0`` to ``1``. ``(0,0)`` is the top-left of the symbol, ``(1,1)`` the bottom-right.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``mse version``	
      - :ref:`version`
      - ''required''
      - Version of MSE this symbol is made with.
    * - ``parts``	
      - :ref:`list` of :ref:`symbol part`s
      -  	
      - The parts in this symbol.

**Example**
Look at a file made with the program.


Settings
~~~~~~~~

**Overview**

The MSE settings are stored in a separate file.

**Location**

On Windows XP the settings are located in:

.. code-block::

     "C:\Documents and Settings\Application Data\Magic Set Editor\mse8.config"

**Properties**
See the settings file for the properties.


Compound Types
--------------

These contain several properties, similair to the file types. But they are part of some other file type.

.. list-table:: 
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - :doc:`field <#field>`
      - A field description for cards.
    * - :doc:`style <#style>`
      - The styling and positioning of a field.
    * - :doc:`value <#value>`
      - The value in a field, for a particular card.
    * - :doc:`card <#card>`
      - A card containing values.
    * - :doc:`keyword <#keyword>`
      - A keyword.
    * - :doc:`keyword mode <#keyword mode>`
      - A possible mode for keywords.
    * - :doc:`keyword param type <#keyword param type>`
      - A type of parameters for keywords.
    * - :doc:`statistics dimension <#statistics dimension>`
      - A dimension for the statistics panel.
    * - :doc:`word list <#word list>`
      - A list of words that can be used for a drop down list in text fields.
    * - :doc:`add cards script <#add cards script>`
      - A script for convienently adding multiple cards to a set.
    * - :doc:`font <#font>`
      - Description of a font.
    * - :doc:`symbol part <#symbol part>`
      - Part of a :doc:`symbol <#symbol>`.
    * - :doc:`control point <#control point>`
      - A point on in a symbol part.

Field
~~~~~

**Overview**

A field is a description of a kind of 'container' to hold a value.

For example the :ref:`value` of a 'text field' is a piece of text, that of a 'color field' a :ref:`color`, etc.

Things that are fields are, "card color" and "card name".
Not a particular color or name, but a description of what a card color and a card name are for a particular :ref:`game`.

Fields are part of the :doc:`/file/style triangle`:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Description	
      - Looks
      - Data
    * - :ref:`Game`	
      - :ref:`Stylesheet`
      - :ref:`Set`
    * - '''Field'''	
      - :ref:`Style`	
      - :ref:`Value`

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``type``	
      - One of:
      - ''required''
      - | Type of field.
        | * ``text``
        | * ``choice``
        | * ``multiple choice``
        | * ``package choice``
        | * ``boolean``
        | * ``image``
        | * ``symbol``
        | * ``color``
        | * ``info``
    * - ``name``	
      - :ref:`string`	
      - ''required''
      - Name of the field.
    * - ``description``	
      - :ref:`localized string`	
      - ``""``	
      - Description of the field, shown in the status bar when the mouse is over the field.
    * - ``icon``	
      - :ref:`filename`
      -  	
      - Filename of an icon for this field, used for automatically generated :ref:`statistics category`s.
    * - ``editable``	
      - :ref:`boolean`
      - ``true``	
      - Can values of this field be edited?
    * - ``save value``	
      - :ref:`boolean`
      - ``true``	
      - Should values of this field be saved to files? Should be disabled for values that are generated by scripts.
    * - ``show statistics``
      - :ref:`boolean`
      - ``true``	
      - | Should a :ref:`statistics dimension` and :ref:`statistics category|category` be made for this field,
        | causing it to be listed on the statistics panel?
    * - ``identifying``	
      - :ref:`boolean`
      - ``false``	
      - Does this field give the name of the :ref:`card` or :ref:`set`?
    * - ``card list column``
      - :ref:`int`	
      - ``0``	
      - On what position in the card list should this field be put?
    * - ``card list width``
      - :ref:`int`	
      - ``100``	
      - Width of the card list column in pixels.
    * - ``card list visible``
      - :ref:`boolean`
      - ``false``	
      - Should this field be shown in the card list by default?
    * - ``card list allow``
      - :ref:`boolean`
      - ``true``	
      - Should this field be allowed in the card list at all?
    * - ``card list name``
      - :ref:`localized string`	
      - field name
      - Alternate name to use for the card list, for example an abbreviation.
    * - ``card list alignment``
      - :ref:`alignment`
      - ``left``	
      - Alignment of the card list column.
    * - ``sort script``	
      - :ref:`script`	
      -  	
      - Alternate way to sort the card list when using this column to sort the list.

The ``type`` determines what values of this field contain:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Type
      - Values contain	
      - Displayed as
    * - ``text``	
      - Text with markup (a :ref:`tagged string`)	
      - Text
    * - ``choice``	
      - A choice from a list
      - Text or an image
    * - ``multiple choice``
      - Zero or more choices from a list
      - A single image or multiple images
    * - ``package choice``
      - A choice from a list of installed :ref:`package`s
      - Text and/or an image
    * - ``boolean``	
      - ``yes`` or ``no``	
      - Text or an image or both
    * - ``color``	
      - Any color or a restricted selection from a list	
      - A box filled with the color
    * - ``image``	
      - Any image	
      - The image
    * - ``symbol``	
      - A :ref:`symbol` edited with the symbol editor	
      - The image
    * - ``info``	
      - An informational message, for example to group fields together.	
      - A box containing the label

Additional properties are available, depending on the type of field:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Type	
      - Property
      - Type	
      - Default	
      - Description
    * - ``"text"``
      - ``script``
      - :ref:`script`	
      -  
      - | Script to apply to values of this field after each change.<br/>
        | If the script evaluates to a constant (i.e. doesn't use ``value``) then values in this field can effectively not be edited.
    * - ^^^	
      - ``default``
      - :ref:`script`	
      -  
      - Script to determine the value when it is in the default state (not edited).
    * - ^^^	
      - ``default name``
      - :ref:`string`
      - ``"Default"``
      - Name of the default state, currently not used.
    * - ^^^	
      - ``multi line``
      - :ref:`boolean`
      - ``false``
      - Can values of this field contain line breaks?
    * - ``"choice"``
      - ``script``
      - :ref:`script`	
      -  
      - | Script to apply to values of this field after each change.<br/>
        | If the script evaluates to a constant (i.e. doesn't use ``value``) then values in this field can effectively not be edited.
    * - ^^^	
      - ``default``
      - :ref:`script`	
      -  
      - Script to determine the value when it is in the default state (not edited).
    * - ^^^	
      - ``initial``
      - :ref:`string`	
      -  
      - Initial value for new values for this field.
    * - ^^^	
      - ``default name``
      - :ref:`string`
      - ``"Default"``
      - Name of the default state.
    * - ^^^	
      - ``choices``
      - :ref:`list` of :ref:`choice`s
      -  
      - Possible values for this field.
    * - ^^^	
      - ``choice colors``
      - :ref:`map` of opaque :ref:`color`s
      -  
      - Colors of the choices for statistics graphs.
    * - ^^^	
      - ``choice colors cardlist``
      - :ref:`map` of opaque :ref:`color`s
      -  
      - Colors of the choices for lines in the card list,<br/> see also the ``card list color script`` property of :ref:`game`s.
    * - ``"multiple choice"``
      -  
      - <<<
      - <<<
      - <<<
		'' Multiple choice fields have the same attributes as normal choice fields.''<br/>
		To refer to a combination of values in the initial attribute use ``choice1, choice2, choice3``.<br/>
		These choices must appear in the same order as they do in the ``choices`` property.
    * - ``"boolean"``
      - ''A boolean field is a choice field with the choices ``"yes"`` and ``"no"``.''
      - <<<
      - <<<
      - <<<
    * - ``"package choice"``
		``script``	:ref:`script`		 	Script to apply to values of this field after each change.<br/>
        | If the script evaluates to a constant (i.e. doesn't use ``value``) then values in this field can effectively not be edited.
    * - ^^^	
      - ``match``	
      - :ref:`string`
      - ''required'' 
      - Filenames of the packages to match, can include wildcards ``"*"``. For example ``"magic-mana-*.mse-symbol-font"``.
    * - ^^^	
      - ``initial``
      - :ref:`string`
      - ''required'' 
      - Initial package for new values for this field.
    * - ^^^	
      - ``reqired``
      - :ref:`boolean`
      - ``true`` 
      - Must a package always be selected? Or is it allowed to select nothing?
    * - ^^^	
      - ``empty name``
      - :ref:`string`
      - ``"None"``
      - Name of the empty state. Applies only if ``required: false``.
    * - ``"color"``
      - ``script``
      - :ref:`script`	
      -  
      - | Script to apply to values of this field after each change.<br/>
        | If the script evaluates to a constant (i.e. doesn't use ``value``) then values in this field can effectively not be edited.
    * - ^^^	
      - ``default``
      - :ref:`script`	
      -  
      - Script to determine the value when it is in the default state (not edited).
    * - ^^^	
      - ``initial``
      - :ref:`string`	
      -  
      - Initial color for new values for this field.
    * - ^^^	
      - ``default name``
      - :ref:`string`
      - ``"Default"``
      - Name of the default state.
    * - ^^^	
      - ``allow custom``
      - :ref:`boolean`
      - ``true``
      - Are colors other then those from the choices allowed?
    * - ^^^	
      - ``choices``
      - :ref:`list` of :ref:`color choice`s
      -  
      - Possible values for this field.
    * - ``"image"``
      - ''no extra properties''
      - <<<
      - <<<
      - <<<
    * - ``"symbol"``
      - ''no extra properties''
      - <<<
      - <<<
      - <<<
    * - ``"info"``
      - ``script``
      - :ref:`script`	
      -  
      - Script to determine the value to show.

**Example**
The ``title`` field gives the title of a set:

.. code-block::

    set field:
    	type: text
    	name: title
    	identifying: true

The border color of cards can be selected from a list of choices, but other values are also possible.
The default is based on a set field. Statistics don't make much sense for the border color.

.. code-block::

    card field:
    	type: color
    	name: border color
    	default: set.border_color
    	choice:
    		name: black
    		color: rgb(0,0,0)
    	choice:
    		name: white
    		color: rgb(255,255,255)
    	choice:
    		name: silver
    		color: rgb(128,128,128)
    	choice:
    		name: gold
    		color: rgb(200,180,0)
    	show statistics: false


Style
~~~~~

**Overview**

A style specifies how a :ref:`field` should look,
things like position, size, fonts, colors, etc.

Styles are part of the :doc:`/file/style triangle`:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Description	
      - Looks
      - Data
    * - :ref:`Game`	
      - :ref:`Stylesheet`
      - :ref:`Set`
    * - :ref:`Field`
      - '''Style'''	
      - :ref:`Value`

**Positioning**

<img src="style-positioning.png" alt="" style="float:right;border:1px solid #ccc;"/>
A style specifies the position of a box for the content.
To specify the horizontal location ''two'' of ``left``, ``width`` and ``right`` must be specified.

For example:

.. code-block::

     left:  10
     width: 20
Implies that ``right`` is 30 pixels.

Similarly:

.. code-block::

     left: 10
     right: 30
Implies the ``width`` is 20.

The same holds for the vertical location and size; ``top``, ``height`` and ``bottom``.

**Rotation**
Rotating a box can be done with the ``angle`` property.
The angle gives a counter clockwise rotation in degrees of the box.
The box is rotated such that the corner for which the position is specified is at the correct position after rotating.

Here are some examples:

|<img src="style-angle-examples.png" alt=""/>
	>red box:
	>       width:  30
	>       height: 25
	>       left:   10
	>       top:    20
	>       angle:  30
	
	>green box:
	>       width:  25
	>       height: 30
	>       left:   10
	>       top:    80
	>       angle:  90
	
	 	>blue box:
	 	>       width:  30
	 	>       height: 25
	 	>       right:  90
	 	>       bottom: 30
	 	>       angle:  30
	 	
	 	>yellow box:
	 	>       width:  20
	 	>       height: 35
	 	>       right:  60
	 	>       bottom: 60
	 	>       angle:  180


**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``z index``	
      - :ref:`int`	
      - ``0``	
      - Stacking of this box, fields with a higher ``z index`` are placed on top of those with a lower index.
    * - ``tab index``	
      - :ref:`int`	
      - ``0``	
      - Index for moving through the fields with the tab key, fields with a lower tab index come first. Otherwise the order is from top to bottom and then left to right.
    * - ``left``	
      - :ref:`scriptable` :ref:`double`
      - ''Required''
      - Distance between left edge of the box and the left of the card in pixels.
    * - ``width``	
      - :ref:`scriptable` :ref:`double`
      - ''Required''
      - Width of the box in pixels.
    * - ``right``	
      - :ref:`scriptable` :ref:`double`
      - ''Required''
      - Distance between right edge of the box and the ''left'' of the card in pixels.
    * - ``top``
      - :ref:`scriptable` :ref:`double`
      - ''Required''
      - Distance between top edge of the box and the top of the card in pixels.
    * - ``height``	
      - :ref:`scriptable` :ref:`double`
      - ''Required''
      - Height of the box in pixels.
    * - ``bottom``	
      - :ref:`scriptable` :ref:`double`
      - ''Required''
      - Distance between bottom edge of the box and the ''top'' of the card in pixels.
    * - ``angle``	
      - :ref:`scriptable` :ref:`int`
      - ``0``	
      - Rotation of this box, in degrees counter clockwise.
    * - ``visible``	
      - :ref:`scriptable` :ref:`boolean`
      - ``true``	
      - Is this field visible at all?
    * - ``mask``	
      - :ref:`image|scriptable image`	
      - ''none''
      - A mask to apply to the box, black areas in the mask become transparent, similar to :doc:`/function#set_mask`.

The rest of the properties depend on the type of :ref:`field` this style is for.

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Type	
      - Property	
      - Type
      - Default	
      - Description
    * - ``"text"``
      - ``font``
      - :ref:`font`	
      - ''Required'' 
      - Font to render the text.
    * - ^^^	
      - ``symbol font``	
      - :ref:`symbol font`
      -  	
      - Font to render symbols in the text (optional).
    * - ^^^	
      - ``always symbol``	
      - :ref:`boolean`
      - ``false``	
      - | Should all text be rendered with symbols?<br/>
        | Text that is not supported by the symbol font is still rendered as normal text.
    * - ^^^	
      - ``allow formating``
      - :ref:`boolean`
      - ``true``	
      - Is custom formating (bold, italic) allowed?
    * - ^^^	
      - ``alignment``	
      - :ref:`scriptable` :ref:`alignment`
      - ``top left``
      - Alignment of the text.
    * - ^^^	
      - ``direction``	
      - :ref:`direction`
      - ``"left to right"``
      - Direction in which the text flows. If set to ``"vertical"`` it is as if a line break is inserted after each character.
    * - ^^^	
      - ``padding left``	
      - :ref:`scriptable` :ref:`double`	
      - ``0``	
      - Padding between the text and the border of the box, in pixels.
    * - ^^^	
      - ``padding right``	
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``padding top``	
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``padding bottom``
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``padding left min``
      - :ref:`scriptable` :ref:`double`	
      - &infin;	
      - Minimal padding around the field.<br/> When the text is scaled down the padding is scaled as well, but it becomes no smaller than this.
    * - ^^^	
      - ``padding right min``
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``padding top min``
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``padding bottom min``
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``line height soft``
      - :ref:`scriptable` :ref:`double`	
      - ``1``	
      - | Multiplier for the line height of 'soft' line breaks. These are breaks caused by wrapping around lines that are too long.<br/>
        | A line height of ``0`` means all lines are in the same position, ``1`` is normal behaviour, ``2`` skips a line, etc.
    * - ^^^	
      - ``line height hard``
      - :ref:`scriptable` :ref:`double`	
      - ``1``	
      - Multiplier for the line height of 'hard' line breaks. These are breaks caused by the enter key.
    * - ^^^	
      - ``line height line``
      - :ref:`scriptable` :ref:`double`	
      - ``1``	
      - Multiplier for the line height of 'soft' line breaks. These are breaks caused by ``"<line>\n</line>"`` tags.
    * - ^^^	
      - ``line height soft max``
      - :ref:`scriptable` :ref:`double`	
      - ''disabled''
      - When there is still vertical room in the text box, increase the line heights to at most these values to spread the text more evenly.
    * - ^^^	
      - ``line height hard max``
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``line height line max``
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``paragraph height``
      - :ref:`double`	
      - ''flexible''
      - | The height of paragraphs. If specified, each paragraph is given this much space, and aligned inside that space as specified by ``alignment``.<br/>
        | A paragraph break is any line break that is not soft (i.e. caused by word wrap or a ``<soft>`` break).
    * - ^^^	
      - ``mask``
      - :ref:`image|scriptable image`
      - ''none''
      - | A mask that indicates where in the box text can be placed.<br/>
        | Text is never put in black areas of the box:<br/>
        | <img src="style-text-mask.png" alt=""/><br/>
        | The same mask image is also used to determine the size and shape of the box.
        | To include a certain pixel in the size/shape but not allow text to be placed there, it can be made dark gray (a value less than 128).
    * - ^^^	
      - ``layout``	
      - :ref:`text layout`	
      - ''automatic''
      - When read from a script, gives information on the layout of text in this box.
    * - ^^^	
      - ``content width``	
      - :ref:`double`	
      - ''automatic''
      - When read from a script, gives the width of the current content in this box. Equivalent to ``layout.width``
    * - ^^^	
      - ``content height``
      - :ref:`double`	
      - ''automatic''
      - When read from a script, gives the height of the current content in this box. Equivalent to ``layout.height``
    * - ^^^	
      - ``content lines``	
      - :ref:`int`	
      - ''automatic''
      - When read from a script, gives the number of lines of the current content in this box. Equivalent to ``length(layout.lines)``
	
!	<<<	<<<	<<<	<<<
    * - ``"choice"``,<br/>``"multiple choice"``,<br/>``"boolean"``
		``popup style``	``"drop down"`` or ``"in place"``		``"drop down"``	Where to place the drop down box for editing the value.<br/>
        | ``"drop down"`` places the box below the field, similar to normal combo boxes.<br/>
        | ``"in place"`` places the box at the mouse coordinates.
    * - ^^^	
      - ``render style``
      - :ref:`render style`	
      - ``"text"``
      - How should the field be rendered?
    * - ^^^	
      - ``combine``
      - :ref:`combine`
      - ``"normal"``
      - How to combine the image with the background? Can be overridden using the :doc:`/function#set_combine` function.
    * - ^^^	
      - ``alignment``
      - :ref:`alignment`
      - ``"stretch"``
      - Alignment of text and images in the box.
    * - ^^^	
      - ``font``	
      - :ref:`font`	
      -  	
      - Font to use for rendering text (depending on ``render style``)
    * - ^^^	
      - ``image``	
      - :ref:`image|scriptable image`	
      -  	
      - | Image to show (depending on ``render style``).<br/>
        | The script will be called with ``input`` set to the value to determine an image for.
    * - ^^^	
      - ``choice images``
      - :ref:`map` of :ref:`image`s	
      -  	
      - | An alternative way to specify what image to show.<br/>
        | For each :ref:`choice` a separate image is specified.
    * - ^^^	
      - ``content width``	
      - :ref:`double`
      - ''automatic''
      - | When read from a script, gives the width of the current choice image in this box. <br/>
        | This is only useful when the alignment is changed, otherwise it is always equal the box size itself.
    * - ^^^	
      - ``content height``
      - :ref:`double`
      - ''automatic''
      - When read from a script, gives the height of the current choice image in this box.
    * - ``"multiple choice"``
		``direction``	:ref:`scriptable` :ref:`direction`	``"left to right"``	Direction the items are laid out in, only when ``render style`` is ``list``.
    * - ^^^	
      - ``spacing``
      - :ref:`scriptable` :ref:`double`
      - ``0``
      - Spacing between the items.
	
!	<<<	<<<	<<<	<<<
    * - ``"package choice"``
    * - ^^^	
      - ``font``	
      - :ref:`font`	
      -  	
      - Font to use for rendering text.
	
!	<<<	<<<	<<<	<<<
    * - ``"color"``
      - ``radius``
      - :ref:`double`	
      - ``0``
      - Radius of rounded corners for the box in pixels.
    * - ^^^	
      - ``left width``
      - :ref:`double`	
      - &infin;
      - Draw only this many pixels from the side, creating a box with a hole in it, or a card border.
    * - ^^^	
      - ``right width``
      - ^^^
      - ^^^
      - ^^^
    * - ^^^	
      - ``top width``
      - ^^^
      - ^^^
      - ^^^
    * - ^^^	
      - ``bottom width``
      - ^^^
      - ^^^
      - ^^^
    * - ^^^	
      - ``combine``
      - :ref:`combine`	
      - ``"normal"``
      - How to combine the color with the background? Only applies when a mask is used.
	
!	<<<	<<<	<<<	<<<
    * - ``"image"``
      - ``default``
      - :ref:`image|scriptable image`	
      - ''none''
      - A default image to use when the card has none.
	
!	<<<	<<<	<<<	<<<
    * - ``"symbol"``
      - ``variations``
      - :ref:`list` of :ref:`symbol variation`s
      -  
      - Available variations of the symbol, a variation describes color and border size.
    * - ^^^	
      - ``min aspect ratio``
      - :ref:`double`	
      - ``1``	
      - Bounds for the aspect ratio, ``width/height`` symbols can take. This can be used to make non-square symbols.
    * - ^^^	
      - ``max aspect ratio``
      - :ref:`double`	
      - ``1``	
      - ^^^
	
!	<<<	<<<	<<<	<<<
    * - ``"info"``
      - ``font``
      - :ref:`font`	
      - ''Required'' 
      - Font to render the text.
    * - ^^^	
      - ``alignment``	
      - :ref:`scriptable` :ref:`alignment`
      - ``top left``
      - Alignment of the text.
    * - ^^^	
      - ``padding left``	
      - :ref:`double`	
      - ``0``	
      - Padding between the text and the border of the box, in pixels.
    * - ^^^	
      - ``padding right``	
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``padding top``	
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``padding bottom``
      - ^^^
      - ^^^	
      - ^^^
    * - ^^^	
      - ``background color``
      - opaque :ref:`color`
      - ``rgb(255,255,255)``
      - Background color for the box, can be used to make it stand out.

**Example**


Render Style
____________

A way to render a choice :ref:`field`, see :ref:`style`.

**Possible values**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Value
      - Sketch	
      - Description
    * - ``text``	
      - | <img src="choice-render-style-text.png" alt=""/>
        | Rendered as text
    * - ``image``	
      - | <img src="choice-render-style-image.png" alt=""/>
        | Rendered as an image
    * - ``both``	
      - | <img src="choice-render-style-both.png" alt=""/>
        | Both an image and text
    * - ``hidden``	
      - | <img src="choice-render-style-hidden.png" alt=""/>
        | The box is hidden, but the value can still be edited.
    * - ``image hidden``
      - | <img src="choice-render-style-hidden.png" alt=""/>
        | The box is hidden, but the value can still be edited.
    * - ``checklist``	
      - | <img src="choice-render-style-checklist-text.png" alt=""/>
        | A list of checkboxes, for multiple choice styles.
    * - ``image checklist``
      - | <img src="choice-render-style-checklist-image.png" alt=""/>
        | A list of checkboxes with images instead of text.
    * - ``both checklist``
      - | <img src="choice-render-style-checklist-both.png" alt=""/>
        | A list of checkboxes with both images and text.
    * - ``text list``	
      - | <img src="choice-render-style-list-text.png" alt=""/>
        | A list of the selected items, for multiple choice styles.
    * - ``image list``	
      - | <img src="choice-render-style-list-image.png" alt=""/>
        | A list of the selected items with images instead of text.
    * - ``both list``	
      - | <img src="choice-render-style-list-both.png" alt=""/>
        | A list of the selected items with both images and text.

**Examples**

.. code-block::

     render style: image

Symbol Variation
________________

**Overview**

A variation of a symbol, describes color and border.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``name``	
      - :ref:`string`	
      - ''Required''
      - Name of this variation, refered to by the :doc:`/function#symbol_variation` function.
    * - ``border radius``
      - :ref:`double`	
      - ``0.05``	
      - Border radius of the symbol.
    * - ``fill type``	
      - | ``solid`` or ``linear gradient`` or ``radial gradient``
        | ``"solid"``	How to fill the symbol.

Depending on the ``fill type`` there are additional properties:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Fill type	
      - Property	
      - Type	
      - Description
    * - ``"solid"``	
      - ``fill color``	
      - :ref:`color`
      - Color to use for filling the symbol.
    * - ^^^
      - ``border color``	
      - :ref:`color`
      - Color to use for the border of the symbol.
    * - ``"linear gradient"``
      - ``fill color 1``	
      - :ref:`color`
      - Color to use for filling the symbol at the center of the gradient.
    * - ^^^
      - ``border color 1``
      - :ref:`color`
      - Color to use for the border of the symbol at the center of the gradient.
    * - ^^^
      - ``fill color 2``	
      - :ref:`color`
      - Color to use for filling the symbol at the ends of the gradient.
    * - ^^^
      - ``border color 2``
      - :ref:`color`
      - Color to use for the border of the symbol at the ends of the gradient.
    * - ^^^
      - ``center x``, ``center y``
      - :ref:`double`
      - Position of the center point of the gradient (in the range 0 to 1)
    * - ^^^
      - ``end x``, ``end y``
      - :ref:`double`
      - Position of the end point of the gradient (in the range 0 to 1)
    * - ``"radial gradient"``
      - ``fill color 1``	
      - :ref:`color`
      - Color to use for filling the symbol at the center of the symbol.
    * - ^^^
      - ``border color 1``
      - :ref:`color`
      - Color to use for the border of the symbol at the center of the symbol.
    * - ^^^
      - ``fill color 2``	
      - :ref:`color`
      - Color to use for filling the symbol at the edges of the symbol.
    * - ^^^
      - ``border color 2``
      - :ref:`color`
      - Color to use for the border of the symbol at the edges of the symbol.

**Examples**
'Common' and 'uncommon' magic expansion symbol styles:

.. code-block::

    variation:
    	name: common
    	border radius: 0.10
    	# White border, black fill
    	fill type: solid
    	fill color:   rgb(0,0,0)
    	border color: rgb(255,255,255)
    variation:
    	name: uncommon
    	border radius: 0.05
    	fill type: linear gradient
    	# Black border, silver gradient fill
    	fill color 1:   rgb(224,224,224)
    	fill color 2:   rgb(84, 84, 84)
    	border color 1: rgb(0,  0,  0)
    	border color 2: rgb(0,  0,  0)

Text Layout
___________

DOC_MSE_VERSION: since 2.0.2

This type contains information on rendered text.

The text is devided into 'lines', 'paragraphs' and 'blocks.
A line is a line on the screen.
A paragraph is one or more lines, ending in an explicit line break, a "\n" in the text.
A block is one or more paragraphs, ending in a line, "<line>\n</line>".

It is possible to dig deeper into blocks, for example


.. code-block::

     card_style.text.layout.blocks[1].lines[0].middle

Is the middle of the first line of the second block.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type
      - Description
    * - ``width``	
      - :ref:`double`	
      - Width of this line or group of lines in pixels.
    * - ``height``
      - :ref:`double`	
      - Height of this line or group of lines in pixels.
    * - ``top``
      - :ref:`double`	
      - Top y coordinate
    * - ``middle``
      - :ref:`double`	
      - Middle y coordinate
    * - ``bottom``
      - :ref:`double`	
      - Bottom y coordinate
    * - ``lines``	
      - :ref:`list` of :ref:`text layout`s
      - The lines in this part of the text.
    * - ``paragraphs``
      - :ref:`list` of :ref:`text layout`s
      - The paragraphs in this part of the text.
    * - ``blocks``
      - :ref:`list` of :ref:`text layout`s
      - The blocks in this part of the text.
    * - ``separators``
      - :ref:`list` of :ref:`double`s
      - The y coordinates of separators between blocks.



Value
~~~~~

**Overview**

A value is something that is 'stored in' a :ref:`field`.

Values are part of the :doc:`/file/style triangle`:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Description	
      - Looks
      - Data
    * - :ref:`Game`	
      - :ref:`Stylesheet`
      - :ref:`Set`
    * - :ref:`Field`
      - :ref:`Style`	
      - '''Value'''

**Possible types**

The type of a value depends on the corresponding field:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Field type	
      - Value data type
      - Description
    * - ``"text"``	
      - :ref:`tagged string`	
      - A piece of text, possibly with markup.
    * - ``"choice"``	
      - :ref:`string`
      - One of the choices of the field.
    * - ``"multiple choice"``
      - :ref:`string`
      - | A list of choices from the field, separated by commas.<br/>
        | For example: ``"red, green, blue"``.
    * - ``"package choice"``
      - Name of a package	
      - The (file)name of a package, including the extension.
    * - ``"boolean"``	
      - ``"yes"`` or ``"no"``	
      - This can be directly used as a :ref:`boolean` value in scripts.
    * - ``"image"``	
      - :ref:`filename`	
      - Filename of an image file in the :ref:`set` package.
    * - ``"symbol"``	
      - :ref:`filename`	
      - | Filename of a :ref:`symbol` file in the :ref:`set` package.<br/>
        | When accessed from a script, image fields can be directly used as :ref:`image`s.
    * - ``"color"``	
      - opaque :ref:`color`	
      - A color.
    * - ``"info"``	
      - :ref:`string`
      - A label for the information box.

**Example**
For the field:

.. code-block::

    field:
    	type: choice
    	name: card color
    	choice: red
    	choice: green
    	choice: blue
A value could be:

.. code-block::

    card color: red


Card
~~~~

**Overview**

A '''card''' in a :ref:`set`.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type
      - Default	
      - Description
    * - ``stylesheet``
      - Name of a :ref:`stylesheet`	
      - ''none''
      - Use a different stylesheet for this card than the :ref:`set`'s default.
    * - ``has styling``
      - :ref:`boolean`
      - false	
      - This card has styling data different from the set's default.
    * - ``styling data``	
      - :ref:`indexmap` of :ref:`value`s
      - false	
      - Styling data, based on the :ref:`stylesheet`'s ``style fields``.
    * - ``notes``
      - :ref:`tagged string`
      - ``""``	
      - Notes for this card.
    * - ``time created``	
      - :ref:`date`	
      - ''now''	
      - Time at which the card was created.
    * - ``time modified``	
      - :ref:`date`	
      - ''now''	
      - Time at which the card was last modified.
    * - ``extra data``
      - | :ref:`map` of :ref:`indexmap`s of :ref:`value`s
        | Data for the 'extra card fields' of the stylesheet.<br/>
        | This is first indexed by stylesheet name, then by field name.
    * - ''remaining keys''	
      - :ref:`indexmap` of :ref:`value`s
      -  	
      - | The remaining keys contain the data for the game's ``card fields``.<br/>
        | So for example ``card.some_field`` corresponds to the value of the card field ``some field``.

**Examples**

With the following game:

.. code-block::

    card field:
    	type: text
    	name: title
    card field:
    	type: color
    	name: card color

A card could look like:

.. code-block::

    card:
    	stylesheet: new
    	has styling: false
    	notes: This card is not finished yet!
    	styling data:
    		extra large cards: true
    	title: My Card
    	card color: rgb(0,128,255)


Keyword
~~~~~~~

**Overview**

A keyword in a :ref:`set` or a :ref:`game`.

A keyword is something that matches a piece of text, and optionally some kind of reminder text can be shown.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``keyword``	
      - :ref:`string`	
      - ''required''
      - Name of the keyword.
    * - ``match``	
      - :ref:`string`	
      - ''required''
      - String to match.
    * - ``reminder``	
      - :ref:`scriptable` :ref:`string`
      - ''required''
      - Script to generate the reminder text of this keyword.
    * - ``rules``	
      - :ref:`string`	
      - ``""``	
      - Explanation or additional rules for this keyword.
    * - ``mode``	
      - Name of a :ref:`keyword mode`	
      -  	
      - Mode of this keyword.

The match string can include parameters, ``"<atom-param>type</atom-param>"`` where ``"type"`` is the name of a :ref:`keyword param type|keyword parameter type` in the game.
These will match according to the ``match`` property of that parameter type.

When expanding the reminder text ``param1`` refers to the first parameter in the match string, ``param2`` to the second, etc.

**Example**

.. code-block::

    keyword:
    	keyword: Equip
    	match: Equip <atom-param>cost</atom-param>
    	mode: core
    	reminder: {param1}: Attach to target creature you control. Equip only as a sorcery.


Keyword Mode
~~~~~~~~~~~~

**Overview**

A mode for :ref:`keyword`s.

This becomes a choice in the 'mode' box on the keywords panel.

The idea behind modes is that a mode indicates what type of keyword it is, for example an "official" keyword, a "simple" keyword or a "custom" keyword.
This information can then be used to determine whether to expand the reminder text.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``name``	
      - :ref:`string`	
      - ''required''
      - Name of the mode, this is shown in the box and used in scripts.
    * - ``description``	
      - :ref:`string`	
      - ``""``	
      - A description of this mode.
    * - ``is default``	
      - :ref:`boolean`
      - ``false``	
      - Is this the default mode for new keywords?

**Example**

.. code-block::

    keyword mode:
    	name: custom
    	description: Custom keywords
    	is default: true


Keyword Param Type
~~~~~~~~~~~~~~~~~~

**Overview**

A type of parameter that can be used in a :ref:`keyword`.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``name``	
      - :ref:`string`	
      - ''required''
      - Name of the parameter type.
    * - ``description``	
      - :ref:`string`	
      - ''required''
      - Description of the parameter type.
    * - ``placeholder``	
      - :ref:`string`	
      - ``name`` of this param type
      - Placeholder to use for empty parameters, the name is used if this is empty.
    * - ``optional``	
      - :ref:`boolean`
      - ``true``	
      - Is a placeholder used when a keyword is encountered with no parameter,<br/> for example ``"Cycling "`` would become ``"Cycling <atom-kwpph>cost</atom-kwpph>"``.
    * - ``match``	
      - :ref:`regex`	
      - ''required''
      - Regular expression that this param type matches.
    * - ``separator before is``
      - :ref:`regex`	
      - ``""``	
      - Regular expression of separator before parameters of this type.
    * - ``separator after is``
      - :ref:`regex`	
      - ``""``	
      - Regular expression of separator after  parameters of this type.
    * - ``eat separator``
      - :ref:`boolean`
      - ``true``	
      - | Allow the user to 'type over' the separator.<br/>
        | For example if the separator is ``" "`` in the keyword ``"Cycling"``, and the user types ``"Cycling"``,
        | a space and a placeholder is automatically inserted, making ``"Cycling <cost>"``.
        | If the user now presses space the cursor is only moved, no additional space is inserted, the space is 'eaten'.
    * - ``script``	
      - :ref:`script`	
      -  	
      - Script to apply to parameters of this type before substituting them back into the text.
    * - ``reminder script``
      - :ref:`script`	
      -  	
      - Script to apply to parameters of this type before using them in the reminder text.
    * - ``example``	
      - :ref:`string`	
      -  	
      - Example for in the keyword editor, currently not used.
    * - ``refer scripts``
      - | :ref:`list` of :ref:`keyword param reference script`s
        | Scripts for inserting parameters of this type into the reminder text.
        | To make this easy for the user, a menu of ways to use a parameter is provided.

**Example**
The 'number' parameter type. It matches a sequence of digits.
It can be included in the reminder text directly, or by applying some function first.

.. code-block::

    keyword parameter type:
    	name: number
    	match: [0-9]+
    	refer script:
    		name: normal
    		description: (1,2,3)
    		script: \{{input}\}
    	refer script:
    		name: as words
    		description: (one, two, three)
    		script: \{english_number({input})\}

Keyword Param Reference Script
______________________________

**Overview**

A way to use a :ref:`keyword param type|keyword parameter` in a :ref:`keyword`'s reminder text.

Usually the parameters are included as ``"{param1}"``, etc.
But in some cases for instance a function should be applied, ``"{fun(param1)}"``.

To make this easy for the user, a menu of choices is provided, this type describes such a choice.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type	
      - Default	
      - Description
    * - ``name``	
      - :ref:`string`
      - ''required''
      - Name of the parameter type.
    * - ``description``	
      - :ref:`string`
      - ''required''
      - A description of the reference script.
    * - ``script``	
      - :ref:`script`
      - ''required''
      - | Script that generates the code using the parameter.<br/>
        | This means you will likely need to do some escaping.<br/>
        | In the script, ``input`` refers to the name of the parameter, for example ``"param1"``.

**Example**
Apply the :doc:`/function#english_number` function to the parameter:

.. code-block::

    refer script:
    	name: as words
    	description: (one, two, three)
    	script: \{english_number({input})\}



Statistics Dimension
~~~~~~~~~~~~~~~~~~~~

**Overview**

A dimension or axis for the statistics panel.

One or more dimensions are combined in a graph, these combinations are called :ref:`statistics category`s.

Statistics dimensions are automatically generated for all card fields in a :ref:`game` that don't set ``show statistics`` to ``false``.

Categories are also automatically generated from dimensions.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``name``	
      - :ref:`string`	
      - ''required''
      - Name of this dimension, used as an axis label and a label for automatically generated categories.
    * - ``description``	
      - :ref:`localized string`	
      - ``""``	
      - A description of the dimension, currently not used.
    * - ``position hint``
      - :ref:`string`	
      - ``0``	
      - Hint for ordering dimensions.
    * - ``icon``	
      - :ref:`filename`
      -  	
      - Filename of an icon for this dimension.
    * - ``script``	
      - :ref:`script`	
      - ''required''
      - Script that generates a value for each card in the set.
    * - ``numeric``	
      - :ref:`boolean`
      - ``false``	
      - Is the value always a number?
    * - ``bin size``	
      - :ref:`double`	
      - ''none''
      - | For numeric dimensions: group numbers together into bins this large.<br/>
        | For example with ``bin size: 5``, values ``1`` and ``3`` both get put under ``"1-5"``.
    * - ``show empty``	
      - :ref:`boolean`
      - ``false``	
      - Should cards with the value ``""`` be included?
    * - ``split list``	
      - :ref:`boolean`
      - ``false``	
      - Indicates the value is a list of the form ``"item1, item2"``. The card is put under both items.
    * - ``colors``	
      - :ref:`map` of opaque :ref:`color`s
      -  
      - Colors to use for specific values
    * - ``groups``	
      - :ref:`list` of :ref:`string`s
      -  
      - Values to always show, and the order to show them in.

**Example**
Automatically generated statistics dimensions look like this:

.. code-block::

    statistics dimension:
    	name: power
    	script: card.power

Specify a specific order and color of values, otherwise they are ordered alphabeticaly and groups with no cards are not shown:

.. code-block::

    statistics dimension:
    	name: color
    	script: card.color
    	group: white
    	group: blue
    	group: black
    	group: red
    	group: green
    	colors:
    		white: rgb(255,255,255)
    		blue:  rgb(0,0,255)
    		black: rgb(0,0,0)
    		red:   rgb(255,0,0)
    		green: rgb(0,255,0)

Word List
~~~~~~~~~

A list of words. Used for drop down lists in the text editor, for example for card types.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type	
      - Default	
      - Description
    * - ``name``
      - :ref:`string`
      - ''Required''
      - Name of this word list, refered to using a ``"<word-list-...>"`` tag.
    * - ``words``
      - :ref:`list` of :ref:`word list word`s
      - ''Required''
      - The words in the list

**Example**

.. code-block::

    word list:
    	name: type
    	word: Creature
    	word: Spell
    	word: Artifact
This can be used with for example:

.. code-block::

     ``"<word-list-type>Creature</word-list-type>"``
Which gives the creature choice, and that can be changed with a drop down list.

Word List Word
~~~~~~~~~~~~~~

A word in a :ref:`word list`.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type	
      - Default	
      - Description
    * - ``name``
      - :ref:`string`
      - ''Required''
      - The word.
    * - ``line below``
      - :ref:`boolean`	
      - ``false``	
      - Display a line below this item in the list?
    * - ``is prefix``
      - :ref:`boolean`	
      - ``false``	
      - | Should this word be used as a prefix before another word from the list?<br/>
        | Think "Legendary ". Note the space after it, words are directly concatenated.
    * - ``words``
      - :ref:`list` of :ref:`word list word`s
      -  	
      - A submenu. If given, the ``name`` of this word is only used as a label for the menu.
    * - ``script``
      - :ref:`script`
      - ''Optional''
      - | A script that determines zero or more words.<br/>
        | The result should be a list of comma separated words, for example ``"x,y,z"`` specifies three words.
        | The words are included in the parent menu, not a sub menu.

A word can also be given in a short form, in that case only the name is specified.

**Example**
In short form:

.. code-block::

    word: xyz
Is the same as:

.. code-block::

    word:
    	name: xyz

Using a script,

.. code-block::

    word:
    	script: "red,green,blue"
    	line below: true
Is the same as

.. code-block::

    word: blue
    word: green
    word:
    	name: red
    	line below: true


Add Cards Script
~~~~~~~~~~~~~~~~

DOC_MSE_VERSION: since 0.3.7

**Overview**

A script to add multiple cards to the set at once.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type
      - Default	
      - Description
    * - ``name``
      - :ref:`string`	
      -  	
      - Name of this script; appears in the menu.
    * - ``description``
      - :ref:`string`	
      - ``""``	
      - Description of this script; appears in the status bar.
    * - ``enabled``
      - :ref:`scriptable` :ref:`boolean`
      - ``true``	
      - Is this script enabled?
    * - ``script``
      - :ref:`script`	
      -  	
      - | Script that produces the cards.<br>
        | This script should return a :ref:`list` of :ref:`card`s.
        | The :doc:`/function#new_card` function can be used to make new cards.

**Example**

.. code-block::

    add cards script:
    	name: &Basic Lands
    	description: Adds 5 basic lands to the set.
    	script:
    		[ new_card([name: "Plains",   super_type: "Basic Land", sub_type: "Plains"])
    		, new_card([name: "Island",   super_type: "Basic Land", sub_type: "Island"])
    		, new_card([name: "Swamp",    super_type: "Basic Land", sub_type: "Swamp"])
    		, new_card([name: "Mountain", super_type: "Basic Land", sub_type: "Mountain"])
    		, new_card([name: "Forest",   super_type: "Basic Land", sub_type: "Forest"])
    		]

When invoked, this script will add the five basic lands to the set.



Font
~~~~

**Overview**

A reference to a normal :ref:`font` for drawing text.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``name``	
      - :ref:`scriptable` :ref:`string`
      - ''required''
      - Name of the font as it appears in most text programs.
    * - ``italic name``	
      - :ref:`scriptable` :ref:`string`
      -  	
      - Optionally, a different font to use for italic text instead of the normal italic version of the font.
    * - ``size``	
      - :ref:`scriptable` :ref:`double`
      - ''required''
      - Size of the font in points on a 96 DPI display.
    * - ``scale down to``
      - :ref:`double`	
      - &infin;	
      - Minimum size in points to scale the size down to.
    * - ``max stretch``	
      - :ref:`double`	
      - ``1.0``	
      - Maximum multiplier by which the width of the text is compressed, so ``max width: 0.5`` means the text can be compressed to half the normal width.
    * - ``weight``	
      - :ref:`scriptable` font weight	
      - ``"normal"``
      - Weight of the font, one of ``"normal"`` or ``"bold"``. This can be changed locally by :ref:`tagged string|tags`.
    * - ``style``	
      - :ref:`scriptable` font style	
      - ``"normal"``
      - Style of the font, one of ``"normal"`` or ``"italic"``. This can be changed locally by :ref:`tagged string|tags`.
    * - ``underline``	
      - :ref:`scriptable` :ref:`boolean`
      - ``false``	
      - Should the font be underlined?
    * - ``color``	
      - :ref:`scriptable` :ref:`color`
      - ``rgb(0,0,0)``
      - What color should text be drawn in?
    * - ``shadow color``
      - :ref:`scriptable` :ref:`color`
      - ``"transparent"``
      - Color for a shadow below the text.
    * - ``shadow displacement x``
      - :ref:`double`
      - ``0``	
      - Relative position of the shadow in pixels.
    * - ``shadow displacement y``
      - :ref:`double`
      - ``0``	
      - ^^^
    * - ``shadow blur``	
      - :ref:`double`	
      - ``0``	
      - How much should the shadow be blurred?
    * - ``separator color``
      - :ref:`color`	
      - ``rgba(0,0,0,128)``
      - Color for ``<sep-soft>`` tags inserted by the :doc:`/function#combined_editor` function.

**Example**

.. code-block::

    font:
    	name: Times new Roman
    	size: 17
    	weight: bold
    	color: rgb(0,0,0)


Symbol Part
~~~~~~~~~~~

**Overview**

A part of a symbol, corresponds to an item you see in the list on the left of the editor.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``type``	
      - One of:
      - ``"shape"``
      - | What type of symbol part is this?
        | * ``shape``
        | * ``group``
        | * ``symmetry``
    * - ``name``	
      - :ref:`string`	
      - ``""``	
      - The name of this part, for the part list.

The rest of the properties depends on the ``type``.

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Type	
      - Property
      - Type
      - Default	
      - Description
    * - ``"shape"``
      - ``combine``
      - :ref:`symbol combine`
      - ``"overlap"``
      - How to combine the shape with those below it?
    * - ^^^	
      - ``points``
      - :ref:`list` of :ref:`control point`s
      -  
      - The points that form this shape
    * - ``"symmetry"``
      - ``kind``	
      - ``rotation`` or ``reflection``	
      - ``"rotation"``
      - What kind of symmetry is this?
    * - ^^^	
      - ``copies``
      - :ref:`int`	
      - 2	
      - How many times is the original copied (including the original itself)?
    * - ^^^	
      - ``center``
      - :ref:`vector2d`
      -  	
      - Coordinates of the center of symmetry.
    * - ^^^	
      - ``handle``
      - :ref:`vector2d`
      -  	
      - Direction perpendicular to the 'mirror' (this is a direction, so relative to the center).
    * - ``"group"`` and ``"symmetry"``
		``parts``		:ref:`list` of :ref:`symbol part`s		 	Parts in this group.


**Example**
Look at a symbol file made with the program.


Control Point
~~~~~~~~~~~~~

**Overview**

A single [[http://en.wikipedia.org/wiki/Bezier_curve|B&eacute;zier curve` control point in a :ref:`symbol part|symbol shape`.

A control point is a point on the polygon.
It also optionally has two 'handles' corresponding to the boxes attached with dotted lines in the editor.

The control points of a shape are circular, the point after the last point in the list is the first point.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``position``	
      - :ref:`vector2d`
      -  	
      - Position of the control point.
    * - ``lock``	
      - ``free``, ``direction`` or ``size``
      - |  ``"free"``
        | Is this point 'locked', i.e. is the relation between the two handles fixed?<br/>
        | If ``lock`` is ``"direction"`` then the two handles must lie on a line.<br/>
        | If ``lock`` is ``"direction"`` then the two handles must lie exactly oppisite each other on the same distance from the point.
    * - ``line after``	
      - ``line`` or ``curve``
      - ``"line"``
      - Is the segment between this control point and the next one in the list a straight line or a cubic B&eacute;zier curve?
    * - ``handle before``
      - :ref:`vector2d`
      -  	
      - Position of the handle for the segment between this point and the previous one, relative to the point's ``position``.<br/>Only when that point's ``line after == "curve"``.
    * - ``handle after``
      - :ref:`vector2d`
      -  	
      - Position of the handle for the segment between this point and the next one, relative to the point's ``position``.<br/>Only when ``line after == "curve"``.

**Example**
Look at a symbol file made with the program.




















Collection Types
----------------

.. list-table:: 
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - :doc:`list <#list>`
      - | Lists of items
        | * item
        | * item
        | * item
    * - :doc:`indexmap <#indexmap>`
      - | Lists indexed by field name
        | <table><tr><td>name:</td><td>someone</td></tr>
        | <tr><td>type:</td><td>something</td></tr></table>
    * - :doc:`map <#map>`
      - Lists indexed by other text

List
~~~~

**File syntax**
In files a list is represented as multiple keys, one for each element.
The keys are all in the singular for of the name of the list,
if the list is named for instance ``symbols`` each key will be named ``symbol``.

.. code-block::

    symbol:
    	# first symbol here
    symbol:
    	# second symbol here
    # etc.

**Script syntax**
In a script lists can be declared using square brackets.

.. code-block::

     []    # An empty list
     [1]   # A list with a single element, the value 1
     [1,2] # A list with two elements

Lists can be accessed using either the bracket operator, or the dot operator.
The first element of a list is numbered 0, the next 1, etc.

.. code-block::

     list.0    # The first element of the list 'list'
     list[0]   # The same thing
     list[0+0] # The same thing

It is possible to iterate over lists using the ``for each`` construct:

.. code-block::

     for each x in [1,2,3] do "x = {x}. "
evaluates to:

.. code-block::

     "x = 1. x = 2. x = 3. "

**Functions**
There are several functions for working with lists:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :doc:`/function#position`	
      - Find the position of an element in a list
    * - :doc:`/function#number_of_items`
      - Return the number of items in a list
    * - :doc:`/function#sort_list`	
      - Sort a list
    * - :doc:`/function#filter_list`	
      - Filter a list, keeping only elements that match a predicate


Field Map
~~~~~~~~~

**Overview**

A 'field map' is a :ref:`map`, but indexed by :ref:`field`s.

For instance if a game specifies the fields:

.. code-block::

    field:
    	type: text
    	name: field1
    field:
    	type: color
    	name: field2

Then the a field map of ''things'' for those fields would look like:

.. code-block::

    field1: thing
    field2: thing

A field map of :ref:`style`s would be:

.. code-block::

    field1: # some text style for field1 goes here
    field2: # some color style for field2 goes here

And a field map of :ref:`value`s would be:

.. code-block::

    field1: text goes here
    field2: rgb(1,2,3)

**Script syntax**

In a script field maps can be accessed like normal :ref:`map`s based on the field name.
So:

.. code-block::

    card.field1 # retrieve the value of field1
    card["field" + 1] # the same thing
    card_style.field2 # retrieve the styling for field2


Map
~~~

A map is like a :ref:`list` with :ref:`string` keys.

**File syntax**
In files a map is represented as key/value pairs.
For instance a map of :ref:`color`s could be:

.. code-block::

    some map:
    	red:   rgb(255,0,0)
    	green: rgb(0,255,0)
    	blue:  rgb(0,0,255)

**Script syntax**
In a script maps can be declared using square brackets.

.. code-block::

     []      # An empty map
     [key:1] # A map with a single element, the value 1 under the key "key"
     [red:rgb(255,0,0), green:rgb(0,255,0)] # A map with two elements

Like lists, maps can be accessed using either the bracket operator, or the dot operator.

.. code-block::

     map.key       # The elment named "key"
     map["k"+"ey"] # The same thing

It is possible to iterate over the values maps using the ``for`` construct:

.. code-block::

     for each x in [one: 1, two: 2] do "x = {x}. "
evaluates to:

.. code-block::

     "x = 1. x = 2. "























Script Related
--------------

.. list-table:: 
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - :doc:`script <#script>`
      - A script to execute to update a field, or for initialization.
    * - :doc:`scriptable <#scriptable>`
      - A primitive type whose value can depend on a script.
    * - :doc:`image <#image>`
      - An image defined by a script.
    * - :doc:`function <#function>`
      - Functions in scripts. These have no direct representation in a file.

Script
~~~~~~

**Overview**

A script object is a piece of code written in the [[script:index|MSE scripting language`.

**File syntax**

A script is given in the same way as a :ref:`string`.

**Example**
A simple :ref:`field` script that converts everything to upper case:

.. code-block::

    script: to_upper(value)

A larger script, changes ``"y"``s to ``"x"``s and ``"a"``s to ``"b"``s:

.. code-block::

    script:
    	new_value := replace(value, match: "x", replace: "y")
    	new_value := replace(value, match: "a", replace: "b")
    	new_value


Scriptable
~~~~~~~~~~

**Overview**

Many :ref:`style` properties are ''scriptable''; their value can be changed by a script.

Consider for example:

.. code-block::

    left: 123
This defines that the left coordinate of a field is 123 pixels.
To script this you can write:

.. code-block::

    left: { if card.name == "" then 100 else 123 }
Now the left position depends on whether or not the name is empty.

**File syntax**
A 'scriptable something' can take three forms:
# It can be a regular 'something'
  >something: 123
# It can be a script that produces 'something', enclosed in curly braces:
  >something: {100 + 23}
# It can be a script that produces 'something', indented and preceded by ``script:``:
  >something:
  >	script: 100 + 23

Note: To use a multiline script the following does not work:

.. code-block::

    something: { 100 +
                 23 }
If the script has multiple lines, it must start on a new line, and be indented with a TAB:

.. code-block::

    something:
    	{ 100 +
    	  23 }
or

.. code-block::

    something:
    	script: 100 +
    	        23


Image
~~~~~

Images are generated using scripts.

It is either given using a :ref:`filename` or as the output of a function.

**File syntax**
The syntax for files is similair to that of :ref:`scriptable` properties:

.. code-block::

     image: image.png
     image: { "image.png" }
     image: { linear_blend(...) }

**Script syntax**
:ref:`Filename`s are implicitly converted to images as needed.

**See also**
The following functions transform images:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :doc:`/function#linear_blend`	
      - Blend two images together using a linear gradient.
    * - :doc:`/function#masked_blend`	
      - Blend two images together using a third mask image.
    * - :doc:`/function#combine_blend`	
      - Blend two images together using a given :ref:`combine|combining mode`.
    * - :doc:`/function#set_mask`	
      - Set the transparancy mask of an image.
    * - :doc:`/function#set_alpha`	
      - Change the transparency of an image.
    * - :doc:`/function#set_combine`	
      - Chnage how the image should be combined with the background.
    * - :doc:`/function#enlarge`	
      - Enlarge an image by putting a border around it.
    * - :doc:`/function#crop`
      - Crop an image, giving only a small subset of it.
    * - :doc:`/function#drop_shadow`	
      - Add a drop shadow to an image.
    * - :doc:`/function#symbol_variation`
      - Render a variation of a :ref:`symbol`.
    * - :doc:`/function#built_in_image`
      - Return an image built into the program.


Function
~~~~~~~~

**Overview**
The [[script:index|scripting language` allows you to define custom functions.

**Syntax**
A piece of code enclosed in curly braces defines a function.

A function can be called using parentheses, for example ``function(argument:value)``.

**Composition**
Functions can be composed using the ``+`` operator, evaluating ``a + b`` first evaluates ``a`` and uses its result as ``input`` for ``b``:

.. code-block::

     example := to_upper + { "result == {input}" }
     example("xyz") == "result == XYZ"

Multiple functions can be changed together like this, this is especially convenient in combination with [[script:default arguments`.

**Example**

.. code-block::

     example := { a + b }
     example(a: 1, b: 2) == 3




















Enumerations
------------

.. list-table:: 
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - :doc:`alignment <#alignment>`
      - Alignment of text and images.
    * - :doc:`direction <#direction>`
      - Direction of text.
    * - :doc:`combine <#combine>`
      - How to combine images with the background.
    * - :doc:`symbol combine <#symbol combine>`
      - How to combine :ref:`symbol part|symbol shapes` with the background.
    * - :doc:`graph type <#graph type>`
      - Type of statistics graphs.

Alignment
~~~~~~~~~

DOC_MSE_VERSION: changed in 0.3.8

Specifies how text and images are aligned in boxes.
An alignment consists of:
* horizontal alignment
* vertical alignment
* (optional) how to fill the text box
* (optional) when to fill the text box

**Script syntax**
In scripts, alignment is passed around as a string.

**Possible values**
The value is a combination of one or more flags, separated by spaces.
These flags can appear in any order.

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Value
      - Description
    * - ``left``	
      - Horizontally, align at the left
    * - ``center``	
      - Horizontally, align in the middle
    * - ``right``	
      - Horizontally, align at the right
    * - ``top``
      - Vertically, align at the top
    * - ``middle``	
      - Vertically, align in the middle
    * - ``bottom``	
      - Vertically, align at the bottom
    * - ``justify``	
      - Fill the box exactly, by moving words apart/together.
    * - ``justify-all``	
      - Fill the box exactly, by moving individual characters apart/together.
    * - ``stretch``	
      - | Fill the box exactly, by stretching the text.<br/>
        | For images: stretch them, but preserve the aspect ratio.
    * - ``if-overflow``	
      - Only apply ``justify``, ``justify-all`` and ``stretch`` when the box is overfull.
    * - ``force``	
      - | Also justify text at the end of a line in a multiline text field.<br/>
        | Normally only lines ending in a soft line break are justified.

**Examples**

.. code-block::

     alignment: top left
     alignment: middle center
     alignment: top left force justify if-overflow
     alignment: { "middle" + " " + "left" }


Direction
~~~~~~~~~

Specifies the direction of text flow in a text box.

**Script syntax**
In scripts, direction is passed around as a string.

**Possible values**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Value
      - Description
    * - ``left to right``
      - Text starts at the left.
    * - ``right to left``
      - Text starts at the right ''(currently not implemented)''
    * - ``top to bottom``
      - Text starts at the top, each character is on a new line.
    * - ``bottom to top``
      - Text starts at the bottom ''(currently not implemented)''
    * - ``horizontal``	
      - Same as ``left to right``.
    * - ``vertical``	
      - Same as ``top to bottom``.

**Examples**

.. code-block::

     direction: horizontal
     direction: top to bottom


Combine
~~~~~~~

This specifies how an image is to be combined with the background.
This is similair to the feature found in more advanced drawing programs.

The formula's are from [[http://www.pegtop.net/delphi/articles/blendmodes/`.

**Script syntax**
In scripts, combine modes are stored as a string.

**Possible values**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Value
      - Description
    * - ``normal``	
      - Normal behaviour, don't combine.
    * - ``add``
      -  
    * - ``subtract``	
      -  
    * - ``stamp``	
      -  
    * - ``difference``	
      -  
    * - ``negation``	
      -  
    * - ``multiply``	
      -  
    * - ``darken``	
      -  
    * - ``lighten``	
      -  
    * - ``color dodge``	
      -  
    * - ``color burn``	
      -  
    * - ``screen``	
      -  
    * - ``overlay``	
      -  
    * - ``hard light``	
      -  
    * - ``soft light``	
      -  
    * - ``reflect``	
      -  
    * - ``glow``	
      -  
    * - ``freeze``	
      -  
    * - ``heat``	
      -  
    * - ``and``	
      - Bitwise and
    * - ``or``	
      - Bitwise or
    * - ``xor``	
      - Bitwise xot
    * - ``shadow``	
      - Dark colors normally, white colors darken the background.
    * - ``symmetric overlay``
      - ``(overlay(a,b) + overlay(b,a)) / 2``

**Examples**

.. code-block::

     combine: overlay
     combine_image(image1: ..., image2: ..., combine: "shadow")



Symbol Combine
~~~~~~~~~~~~~~

Specifies how symbol shapes are combined with those below it

**Script syntax**
In scripts, symbol combine modes are passed around as a string.

**Possible values**
The value is one of the following options:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Value
      - Description
    * - ``overlap``	
      - Place this shape on top of those below it.<br/> Further combine options only apply to this shape.
    * - ``merge``	
      - Marge this shape with the one below it, they are considered a single shape for further combining.
    * - ``subtract``	
      - Subtract this shape from the one below it.
    * - ``intersection``
      - Take the intersection of this shape and the one below it, only areas that are in both shapes remain.
    * - ``difference``	
      - Take the difference of this shape and the one below it, only areas that are in exactly one of the shapes remain.
    * - ``border``	
      - Use this shape as additional border for the shape below it.

**Examples**

.. code-block::

     combine: overlap


Graph Type
~~~~~~~~~~

Types of graphs for the statistics panel.

**Possible values**
The value is one of the following options:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Value	
      - Dimensions
      - Sketch
      - Description
    * - ``bar``	
      - 1	
      - | <img src="graph-type-bar.png" alt="bar graph"/>
        | One bar for each value on the axis, the height represent the number of cards with that value.
    * - ``pie``	
      - 1	
      - | <img src="graph-type-pie.png" alt="pie graph"/>
        | A pie graph, the size of the slice represents the numer of cards with a particular value.
    * - ``stack``
      - 2	
      - | <img src="graph-type-stack.png" alt="stack graph"/>	
        | One bar for each value on the first axis, bars for each value on axis2 are stacked on top of each other.
    * - ``scatter``
      - 2	
      - | <img src="graph-type-scatter.png" alt="scatter graph"/>
        | Scatter plot, the size of the circles corresponds to the number of cards with those two values.
    * - ``scatter pie``
      - 3	
      - | <img src="graph-type-scatter-pie.png" alt="scatter-pie graph"/>
        | Scatter plot, the size of the circles corresponds to the number of cards with those two values.
        | Each circle is a small pie graph for the third axis.

**Examples**

.. code-block::

     type: bar





















Primitive Types
---------------

.. list-table:: 
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - :doc:`string <#string>`
      - Text, ``"abc"``
    * - :doc:`tagged string <#tagged string>`
      - Text with tags
    * - :doc:`filename <#filename>`
      - Filenames
    * - :doc:`regex <#regex>`
      - Regular expression strings
    * - :doc:`boolean <#boolean>`
      - ``true`` or ``false``
    * - :doc:`int <#int>`
      - Integer numbers, ``1, 2, 100``
    * - :doc:`double <#double>`
      - Real numbers, ``1, 0.5, 21.3``
    * - :doc:`version <#version>`
      - Version numbers
    * - :doc:`color <#color>`
      - Colors
    * - :doc:`date <#date>`
      - Dates/times

String
~~~~~~

A string is just a piece of text.

**File syntax**
In files, strings are written just as their value:

.. code-block::

     string: this is some string
The whitespace at the beginning is removed by the program.
Multiline strings are written on a new line, indented by a TAB:

.. code-block::

     string:
    	This is a very long string
    	It contains a line break.

**Script syntax**
In scripts, strings are written between double quotes, ``"this is a string"``.
The backslash character is used to escape values:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Code
      - Represents
    * - ``\"``
      - A " character
    * - ``\{``
      - A { character
    * - ``\n``
      - A newline character (line break)
    * - ``\\``
      - A backslash
    * - ``\<``
      - An escaped &lt; for :ref:`tagged string`s.

Sections between curly braces are interpreted as script code, that is concatentated with the string, for example

.. code-block::

     "ab{1 + 1}c" == "ab2c"
This can be nested arbitrarily.

The ``+`` operator concatenates strings. Numbers and most other values are automatically converted to strings when needed. This conversion can be forced with the :doc:`/function#to_string` function.

Using the ``[]`` or ``.`` operator characters in a string can be selected. 0 is the first character:

.. code-block::

     "xyz"[0]  ==  "x"
     "xyz".0   ==  "x"  # same thing
     "xyz".1   ==  "y"
     "xyz".2   ==  "z"
It is an error to select characters outside the string

.. code-block::

     "xyz".10  # error

**See also**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :ref:`tagged string`
      - A string containg tags.
    * - :doc:`/function#to_string`	
      - Convert any value to a :ref:`string`


Tagged String
~~~~~~~~~~~~~

**Syntax**
Strings in :ref:`value|text values` can contain markup tags.
These tags affect the presentation and sometimes the behaviour of the text.

A tag is something like ``"<tag>some text</tag>"``, similar to HTML.
Tags are closed by the same tag with a ``/`` before it.

To represent the character ``"<"`` in a tagged string use ``"\<"`` in script code.
This is written as the character with code 1 in files.

**Basic markup**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Tag
      - Description
    * - ``<b>``
      - The text inside the tag is bold.
    * - ``<i>``
      - The text inside the tag is italic.
    * - ``<sym>``	
      - The text inside the tag is rendered as symbols, if a [[prop:style:symbol font` is set for the text box.
    * - ``<color:???>``	
      - The text inside the tag is rendered with the given :ref:`color`.
    * - ``<size:???>``	
      - The text inside the tag is rendered with the given font size in points, for example ``"<size:12>text</size>"`` makes the text 12 points. The text is scaled down proportionally when it does not fit in a text box and the ``scale down to`` attribute allows it.
    * - ``<font:???>``	
      - The text inside the tag is rendered with the given font family.
    * - ``<align:???>``
      - The block inside the tag is aligned with the given horizontal :ref:`alignment`
    * - ``<margin:??:??>``
      - The block inside the tag has additional left, right (optional), and top (optional) margins of the specified size in pixels.
    * - ``<li>``
      - The text inside the tag is treated as a list marker, meaning that if the line wraps it will be indented to match the content of the ``<li>`` tag.
    * - ``<line>``	
      - Line breaks inside this tag use the [[prop:style:line height line`, and they show a horizontal line.
    * - ``<soft-line>``	
      - Line breaks inside this tag use the [[prop:style:soft line height`.
    * - ``<atom>``	
      - | An atomic piece of text. The cursor can never be inside it; it is selected as a whole.
        | The program automatically inserts ``<atom-soft>``.
    * - ``<code>``	
      - The text inside the tag is rendered in a monospace font. This is used for syntax highlighting script code.
    * - ``<code-kw>``	
      - The text inside the tag is highlighted as a keyword in source code.
    * - ``<code-str>``	
      - The text inside the tag is highlighted as a string in source code.

**Other tags**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Tag
      - Description
    * - ``<kw-?>``	
      - | Indicates that the text inside it is a keyword. This tag is automatically inserted by
        | The :doc:`/function#expand_keywords` function.<br/>
        | There are four versions, indicating whether or not reminder text is shown:
        | * ``<kw-0>``, Reminder text hidden, by default
        | * ``<kw-1>``, Reminder text shown, by default
        | * ``<kw-a>``, Reminder hidden manually
        | * ``<kw-A>``, Reminder shown manually
    * - ``<sep>``	
      - | A separator between fields. This tag is automatically inserted by the :doc:`/function#combined_editor` function.<br/>
        | Inserting this tag manually will confuse that function!<br/>
        | This tag can never be selected, and its contents can not be edited.
    * - ``<prefix>``	
      - At the beginning of a string, indicates a part that can not be selected. This tag is automatically inserted by the :doc:`/function#combined_editor` function.
    * - ``<suffix>``	
      - At the end of a string, indicates a part that can not be selected. This tag is automatically inserted by the :doc:`/function#combined_editor` function.
    * - ``<sep-soft>``	
      - Like ``<sep>``, only hidden. This is inserted by :doc:`/function#combined_editor`
    * - ``<soft>``	
      - Text who's width is ignored for alignment, similar to ``<sep-soft>``, but not a separator.
    * - ``<word-list-???>``
      - | Indicate that the text inside the tag should be selected from a :ref:`word list`.
        | The ``???`` must be the name of a word list in the game.
    * - ``<error>``	
      - The text inside the tag is an error, and is shown with a red wavy underline.
    * - ``<error-spelling:???>``
      - | A spelling error, marked by the :doc:`/function#:check_spelling` function.
        | The ``???`` part indicates the language used for spelling checking.
    * - any other tag	
      - Other tags are ignored.


**Related functions**
The following script functions deal with tags:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :doc:`/function#tag_contents`	
      - Change the contents of a specific tag.
    * - :doc:`/function#remove_tag`	
      - Remove a tag, keep the contents.
    * - :doc:`/function#remove_tags`	
      - Remove all tags from tagged text.
    * - :doc:`/function#to_text`	
      - Remove all tags from tagged text, and convert it to a :ref:`string`.


Localized String
~~~~~~~~~~~~~~~~

A 'localized string' is a :ref:`map` of :ref:`:string`s, indexed by locale name.
It is used to translate games and stylesheets to other user interface languages.

Localized strings can be given with a ``localized`` prefix on the property name.
For example, a field has a ``description`` which is a :ref:`:string`, and a ``localized_description`` for localized variants. So


.. code-block::

    field:
    	name: cost
    	description: How much this card costs
    	localized description:
    		en_US: How much this card costs
    		nl_NL: Hoeveel deze kaart kost


Filename
~~~~~~~~

Filenames are regular :ref:`string`s, pointing to a file.
There are two types of filenames, relative and absolute:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Syntax	
      - Description
    * - ``path/to/file``
      - | A relative file, this is retrieved from the current package.
        | i.e. for a filename in a stylesheet, the file is retrieved from that stylesheet.
    * - ``/package/path/to/file``
      - An absolute filename includes the name of the package. This is a package somewhere in the MSE data directory.

Don't forget the double quotes (``""``) in scripts.

**Dependencies**
When using an absolute filename to refer to a file from another :doc:`/file/package`,
the :ref:`dependency` on that package must be declared.
For example,

.. code-block::

    include file: /common.mse-include/something
Will give a warning message, unless the file also lists

.. code-block::

    depends on:
    	package: common.mse-include
    	version: 2007-01-01


Dependency
__________

**Overview**

:ref:`Package`s can depend on other packages.
For example a :ref:`stylesheet` needs a particular version of the corresponding :ref:`game` package, and maybe some additional :ref:`include`s.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type
      - Description
    * - ``package``
      - :ref:`string`	
      - Filename of the package this package depends on.
    * - ``version``
      - :ref:`version`
      - Minimal version of that package that is required.

The two properties can also be written on a single line, separated by a space (see the examples).

**Example**
The magic-new stylesheet depends on a particular version of the game file:

.. code-block::

    depends on:
    	package: magic.mse-game
    	version: 2007-06-06
This can be written more compactly as

.. code-block::

    depends on: magic.mse-game 2007-06-06



Regex
~~~~~

Regular expressions (regexes) are things that can match parts of :ref:`string`s.

Regexes are represented by normal :ref:`string`s.
Note that to escape something in a regex the backslash is used, in script code this also needs to be escaped.
For example, in a script, the regex matching a single backslash is ``"\\\\"``.

For more information, see
[[http://www.wxwidgets.org/manuals/stable/wx_wxresyn.html|the wxWidgets regular expression documentation`.


Boolean
~~~~~~~

A boolean is either ``true`` or ``false``.

In a script, numbers are implicitly converted to booleans, a non-zero number is ``true``, 0 is ``false``.

When converted to a number, ``true`` becomes ``1`` and ``false`` becomes ``0``.

The strings ``"yes"`` and ``"no"`` can also be converted to booleans.

**File syntax**

.. code-block::

     boolean: true
     boolean: false

**Script syntax**

.. code-block::

     true or false

The operators ``or``, ``and`` and ``xor`` combine two booleans:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - ``a``	
      - ``b``	
      - ``a or b``
      - ``a and b``
      - ``a xor b``
    * - ``false``
      - ``false``	
      - ``false``	
      - ``false``	
      - ``false``
    * - ``false``
      - ``true``	
      - ``true``	
      - ``false``	
      - ``true``
    * - ``true``
      - ``false``	
      - ``true``	
      - ``false``	
      - ``true``
    * - ``true``
      - ``true``	
      - ``true``	
      - ``true``	
      - ``false``

**See also**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :doc:`/function#to_boolean`	
      - Convert a value to a boolean


Int
~~~

Integer numbers are numbers without a decimal point.
In many cases negative numbers don't make sense, but the program never complains about them.

**File syntax**

.. code-block::

     something: 123

**Script syntax**

.. code-block::

     123 + 456 * -1

**See also**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :ref:`double`	
      - Number type that can contain fractional values.
    * - :doc:`/function#to_int`	
      - Convert a value to an integer number


Double
~~~~~~

Real or floating point numbers are numbers with a decimal point.

Conversion from integer to real numbers happens automatically in scripting.

**File syntax**

.. code-block::

     something: 123
     something: 0.5

**Script syntax**

.. code-block::

     123.1 + 456 * -1

**See also**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :ref:`int`	
      - Integer numbers
    * - :doc:`/function#to_real`
      - Convert a value to a real number


Version
~~~~~~~

**File syntax**
A version number consists of three components, in the form "a.b.c".
Higher numbers mean newer versions.

The version number can also be a date, of the form "YYYY-MM-DD"

**Examples**

.. code-block::

     version: 1.2.3
     version: 2007-07-12


Color
~~~~~

**Syntax**
In files and scritps a color can be represented as
<pre><span class='hl-kw'>rgb</span>(<i>red_component</i>, <i>green_component</i>, <i>blue_component</i>)</pre>
where red_component, green_component and blue_component are numbers between 0 and 255 (inclusive).

In most places MSE also supports colors with a transparency value, notated as
<pre><span class='hl-kw'>rgba</span>(<i>red_component</i>, <i>green_component</i>, <i>blue_component</i>, <i>alpha_component</i>)</pre>
An alpha value of ``0`` indicates a transparent color, an alpha value of ``255`` is completely opaque.

You can also use HTML style hexadecimal colors,
<pre>#<i>rgb</i>, #<i>rgba</i>, #<i>rrggbb</i>, #<i>rrggbbaa</i></pre>
For example, ``#ff0000`` is red, as is ``#f00``

**Named colors**
MSE also supports named colors, for instance ``"white"`` is the same as ``rgb(255,255,255)``.
For a full list of supported colors, see [[https://docs.wxwidgets.org/3.0/classwx_colour_database.html|the wxWidgets documentation`.
In addition, the named color ``"transparent"`` stands for the completely transparent color, ``rgba(0,0,0,0)``.

In scripts named colors are represented as :ref:`string`s.

**Examples**
For example:

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Code
      - Represents	
      - <<<
    * - ``rgb(255,255,255)``
      - white
      - <div style="border:1px solid black; background:white;width:30px;height:15px;"> </div>
    * - ``rgb(0,0,0)``	
      - black
      - <div style="border:1px solid black; background:black;width:30px;height:15px;"> </div>
    * - ``rgb(255,0,0)``
      - red
      - <div style="border:1px solid black; background:red;  width:30px;height:15px;"> </div>
    * - ``rgb(0,255,0)``
      - green
      - <div style="border:1px solid black; background:rgb(0,255,0);width:30px;height:15px;"> </div>
    * - ``rgb(0,0,255)``
      - blue
      - <div style="border:1px solid black; background:blue; width:30px;height:15px;"> </div>
    * - ``rgba(0,0,0,0)``
      - transparent	
      - <div style="border:1px solid black; width:30px;height:15px;text-align:center;">over</div>
    * - ``rgba(255,0,0,128)``
      - transparent red	
      - <div style="border:1px solid black; background:rgb(255,128,128);color:rgb(128,0,0);width:30px;height:15px;text-align:center;">over</div>
    * - ``rgba(0,0,255,192)``
      - transparent blue
      - <div style="border:1px solid black; background:rgb(64,64,255);color:rgb(0,0,192);width:30px;height:15px;text-align:center;">over</div>

**See also**
    * - :doc:`/function#to_color`	
      - Convert any value to a color

Date
~~~~

DOC_MSE_VERSION: since 0.3.8

A point in time, consisting of a date and a time.
The file syntax uses [[http://en.wikipedia.org/wiki/ISO_8601|ISO 8601` notation.

**File syntax**

.. code-block::

     something: 2008-12-31 23:59:59

**See also**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - :doc:`/function#to_date`
      - Convert a value to a date
    * - :doc:`/function#to_string`
      - Convert dates to strings



Choice
~~~~~~

A possible choice for a choice :ref:`field`.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property	
      - Type
      - Default	
      - Description
    * - ``name``	
      - :ref:`string`	
      - ''Required''
      - Name of this choice, displayed in the drop down list.
    * - ``line below``	
      - :ref:`boolean`
      - ``false``	
      - Display a line below this item?
    * - ``group choice``
      - :ref:`string`	
      - ''no''	
      - Can this submenu of choices itself be selected?
    * - ``choices``	
      - :ref:`list` of :ref:`choice`s
      -  
      - Submenu of choices.
    * - ``enabled``	
      - :ref:`scriptable` :ref:`boolean`
      -  
      - Is this choice selectable?
    * - ``type``	
      - ``"check"`` or ``"radio"``
      - ``"check"``
      - | How should this choice be displayed? As a checkbox or a radio box?<br/>
        | Only applies to multiple choice fields.

A choice can also be given in a short form, in that case only the name is specified.

**Names**

The full name of a choice is that of the choice and its parents, separated by spaces.
This is the value actually stored in values and manipulated by scripts.

For example

.. code-block::

    field:
    	type: choice
    	choice:
    		name: large
    		choice: red
    		choice: blue
    	choice:
    		name: small
    		group choice: just small
    		choice: green
    		choice: yellow

The choice red is called ``"large red"``, while green is ``"small green"``.
The group choice 'just small' gets the name of the group, ``"small"``.

**Example**
In short form:

.. code-block::

    choice: apples
Is the same as:

.. code-block::

    choice:
    	name: apples

Color Choice
~~~~~~~~~~~~

A possible choice for a color :ref:`field`.

**Properties**

.. list-table:: 
    :header-rows: 1
    :stub-columns: 1
    :align: left

    * - Property
      - Type
      - Description
    * - ``name``
      - :ref:`string`	
      - Name of this choice, displayed in the drop down list.
    * - ``color``
      - opaque :ref:`color`
      - Color this choice corresponds with.

**Example**

.. code-block::

    choice:
    	name: red
    	color: rgb(255,0,0)


Vector2D
~~~~~~~~

AKA: Two Dimensional Vector

A coordinate or direction in a symbol.
This is a pair of :ref:`double`s.

The coordinates are usually in the range ``0`` to ``1``.
``(0,0)`` is the top-left of the symbol, ``(1,1)`` the bottom-right.

**File syntax**

.. code-block::

     (x-coordinate,y-coordinate)
For example

.. code-block::

     (0.5,0.5)

**Script syntax**
Vectors can not be represented in script syntax.












