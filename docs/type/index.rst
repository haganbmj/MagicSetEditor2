Data Types
============

Magic Set Editor uses many data types in the files and in scripting.
There are for instance [[type:card]]s in [[type:set]]s, [[type:stylesheet]]s describing the layout of [[type:field]]s, etc.

File Types
----------

These are the 'major' data types that are written directly to [[file:packages]].

.. list-table:: 
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - :doc:`Game <#game>`
      - What information is on each card?
    * - :doc:`Stylesheet <#stylesheet>`
      - What do cards look like?
    * - :doc:`Set <#set>`
      - Sets of cards.
    * - :ref:`Symbol font <symbol font>`
      - Fonts consisting of symbols, for instance mana symbols.
    * - :ref:`Export template <export-template>`
      - How to export sets to HTML files?
    * - :doc:`Locale <#Locale>`
      - Translations of MSE.
    * - :doc:`Include <#Include>`
      - Files to include in other templates.
    * - :doc:`Installer <#Installer>`
      - Installers containing several packages.
    * - :doc:`Symbol <#Symbol>`
      - Expansion symbols.
    * - :doc:`Settings <#Settings>`
      - MSE settings.

--Compound types--
These contain several properties, similair to the file types. But they are part of some other file type.
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
    * - :doc:`statistics category <#statistics category>`
      - A category for the statistics panel.
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

--Collection types--
    * - :doc:`list <#list>`
      - Lists of items
			* item
			* item
			* item
    * - :doc:`indexmap <#indexmap>`
      - Lists indexed by field name
			<table><tr><td>name:</td><td>someone</td></tr>
			<tr><td>type:</td><td>something</td></tr></table>
    * - :doc:`map <#map>`
      - Lists indexed by other text

--Script related--
    * - :doc:`script <#script>`
      - A script to execute to update a field, or for initialization.
    * - :doc:`scriptable <#scriptable>`
      - A primitive type whose value can depend on a script.
    * - :doc:`image <#image>`
      - An image defined by a script.
    * - :doc:`function <#function>`
      - Functions in scripts. These have no direct representation in a file.

--Enumerations--
    * - :doc:`alignment <#alignment>`
      - Alignment of text and images.
    * - :doc:`direction <#direction>`
      - Direction of text.
    * - :doc:`combine <#combine>`
      - How to combine images with the background.
    * - :doc:`symbol combine <#symbol combine>`
      - How to combine [[type:symbol part|symbol shapes]] with the background.
    * - :doc:`graph type <#graph type>`
      - Type of statistics graphs.

--Primitive types--
    * - :doc:`string <#string>`
      - Text, @"abc"@
    * - :doc:`tagged string <#tagged string>`
      - Text with tags
    * - :doc:`filename <#filename>`
      - Filenames
    * - :doc:`regex <#regex>`
      - Regular expression strings
    * - :doc:`boolean <#boolean>`
      - @true@ or @false@
    * - :doc:`int <#int>`
      - Integer numbers, @1, 2, 100@
    * - :doc:`double <#double>`
      - Real numbers, @1, 0.5, 21.3@
    * - :doc:`version <#version>`
      - Version numbers
    * - :doc:`color <#color>`
      - Colors
    * - :doc:`date <#date>`
      - Dates/times

Game
~~~~

Stylesheet
~~~~~~~~~~

Set
~~~

Symbol Font
~~~~~~~~~~~

Export Template
~~~~~~~~~~~~~~~
