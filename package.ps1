# Super basic build script for release versions.
# Note the hardcoded version numbers which don't read from CMakeLists at all.

# Set alias for 7zip
$7zipPath = "$env:ProgramFiles\7-Zip\7z.exe"

if (-not (Test-Path -Path $7zipPath -PathType Leaf)) {
throw "7 zip file '$7zipPath' not found"
}

Set-Alias 7z $7zipPath

# Cleanup and Recreate the working directories.
Remove-Item .\out\temp -Recurse
Remove-Item .\out\dist -Recurse

New-Item -Type dir .\out\temp\x64 -Force
New-Item -Type dir .\out\temp\x86 -Force
New-Item -Type dir .\out\temp\data -Force

# Copy locale files to a temp directory.
Copy-Item ./data/en.mse-locale/		./out/temp/data/en.mse-locale/ -Force -Recurse
Copy-Item ./data/ch-s.mse-locale/	./out/temp/data/ch-s.mse-locale/ -Force -Recurse
Copy-Item ./data/ch-t.mse-locale/	./out/temp/data/ch-t.mse-locale/ -Force -Recurse
Copy-Item ./data/da.mse-locale/		./out/temp/data/da.mse-locale/ -Force -Recurse
Copy-Item ./data/es.mse-locale/		./out/temp/data/es.mse-locale/ -Force -Recurse
Copy-Item ./data/fr.mse-locale/		./out/temp/data/fr.mse-locale/ -Force -Recurse
Copy-Item ./data/it.mse-locale/		./out/temp/data/it.mse-locale/ -Force -Recurse
Copy-Item ./data/jp.mse-locale/		./out/temp/data/jp.mse-locale/ -Force -Recurse
Copy-Item ./data/pl.mse-locale/		./out/temp/data/pl.mse-locale/ -Force -Recurse
Copy-Item ./data/pt-br.mse-locale/	./out/temp/data/pt-br.mse-locale/ -Force -Recurse
Copy-Item ./data/ru.mse-locale/		./out/temp/data/ru.mse-locale/ -Force -Recurse
Copy-Item ./data/ko.mse-locale/		./out/temp/data/ko.mse-locale/ -Force -Recurse

# Strip any prefixes added by the localization tools.
(Get-Content ./out/temp/data/ch-s.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')	| Set-Content ./out/temp/data/ch-s.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/ch-t.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')	| Set-Content ./out/temp/data/ch-t.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/da.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/da.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/es.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/es.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/fr.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/fr.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/it.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/it.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/jp.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/jp.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/pl.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/pl.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/pt-br.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')	| Set-Content ./out/temp/data/pt-br.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/ru.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/ru.mse-locale/locale -encoding UTF8
(Get-Content ./out/temp/data/ko.mse-locale/locale -encoding UTF8).Replace('#_ADD', '')		| Set-Content ./out/temp/data/ko.mse-locale/locale -encoding UTF8

# Gather the relevant x64 files and Zip them.
Copy-Item ./BUNDLED_README.txt ./out/temp/x64/README.txt -Force -Recurse
Copy-Item ./out/build/x64-Release-static/magicseteditor.com ./out/temp/x64/ -Force -Recurse
Copy-Item ./out/build/x64-Release-static/magicseteditor.exe ./out/temp/x64/ -Force -Recurse
Copy-Item ./out/build/x64-Release-static/magicseteditor-cli.exe ./out/temp/x64/ -Force -Recurse
#Copy-Item ./data/en.mse-locale/ ./out/temp/x64/data/en.mse-locale/ -Force -Recurse
Copy-Item ./out/temp/data/ ./out/temp/x64/data/ -Force -Recurse

7z a -tzip ./out/dist/MagicSetEditor-2.5.0-unofficial-win64.zip ./out/temp/x64/**

# Gather the relevant x86 files and Zip them.
Copy-Item ./BUNDLED_README.txt ./out/temp/x86/README.txt -Force -Recurse
Copy-Item ./out/build/x86-Release-static/magicseteditor.com ./out/temp/x86/ -Force -Recurse
Copy-Item ./out/build/x86-Release-static/magicseteditor.exe ./out/temp/x86/ -Force -Recurse
Copy-Item ./out/build/x86-Release-static/magicseteditor-cli.exe ./out/temp/x86/ -Force -Recurse
#Copy-Item ./data/en.mse-locale/ ./out/temp/x86/data/en.mse-locale/ -Force -Recurse
Copy-Item ./out/temp/data/ ./out/temp/x86/data/ -Force -Recurse

7z a -tzip ./out/dist/MagicSetEditor-2.5.0-unofficial-win32.zip ./out/temp/x86/**
