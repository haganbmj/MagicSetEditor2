File Formats
============

MSE uses several different types of :doc:`data files <format>`, usually organized into :doc:`packages <package>`.

File Types
----------

The following types are stored in :doc:`packages <package>` in the:

* :doc:`game </type/game>`
* :doc:`stylesheet </type/stylesheet>`
* :doc:`symbol font </type/symbol font>`
* :doc:`export template </type/export template>`
* :doc:`locale </type/locale>`
* :doc:`include </type/include>`

The following types are stored in :doc:`packages <package>` that can be located anywhere:

* :doc:`set </type/set>`
* :doc:`installer </type/installer>`

The following types are stored diractly in :doc:`hierarchical files <format>`, they can be located anywhere:

* :doc:`symbol </type/symbol>`

Data Directories
----------------

The data files that come with Magic Set Editor are stored in :doc:`packages <package>` in the ``data`` directory,
these are usually subdirectories of that directory.

There are two data directories, a *global* one with data files installed with the program,
and a *local* data directory for the current logged in user.
The latter is used for installing packages if the user doesn't have administrator priviliges.

.. list-table:: On Windows
    :class: center
    :header-rows: 0
    :stub-columns: 1
    :align: left

    * - Global
      - ``%MSE_DIR%\data``
    * - Local
      - ``%AppData%\Magic Set Editor\data``

.. toctree:: 
    :hidden:

    format
    package
