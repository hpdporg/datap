[![Build Status](https://dev.azure.com/lewissall/hpdporg/_apis/build/status/hpdporg.datap?branchName=master)](https://dev.azure.com/lewissall/hpdporg/_build/latest?definitionId=1&branchName=master)

# datap #

**datap** provides data processing utilities. This library is used in other projects as a dependency. It is not meant as a standalone project.


## Features ##

* Nestable Linked list: Basic dynamic data structure with a super-simple interface, i.e. no iterators. List items can be organized hierarchically. Lists can be tacked on to the end of one another "extended" with ease. 
* Filestore access: New files, file removal, appending, overwriting, path building, and file in directory listing.
* Text matching and extraction: Matches text occurrences in String using 'flags' (think regex), find occurrence/match by index or true/false, substring, List of Strings to String conversion
* Text replacement and aggregation: Replace every occurence of a wildcard with text or List of text Strings (think sed), Text copying, appending
* Text and number conversion: Numbers to letters (binary numeric to alphanumeric), conversion from List of Strings to single text String
* Memory allocation

## Usage ##
* You can use the prebuilt library or build from source on your platform.
* You can use from assembly or link against the function signatures with the C API. A datap.h header is included.
* See the examples, tests, and example source files to gain familiarity.

## Building ##
* Includes pre-built, along with VS projects.
* Includes GoogleTest Unit tests.
* Includes the **fasmg** assembler as an external library.

## Platforms ##
* x86_64, Windows only
* (Other platform support may follow)

