# cio

An addon for Node.js written in C++.

Simple input and output on console.

# Functions

## cio.input()

Returns a string type value without receiving spaces.

## cio.input(type)

Returns a value of specific type.

**String type**: specific type that should be returned
  Possible value: 'Number' | 'String' | 'Boolean'

## cio.input(type, len[, convert])

Returns an array.

**String type**: specific type that should be returned
  Possible value: 'Array'

**Number len**: the length of array that should be read

**Boolean convert**: whether array elements should be converted into String type.
  Possible value: true | false
  Default value: false

## cio.readline()

Returns a string type value and spaces can be received.

## cio.output()

Print `\n` to console.

## cio.output(str[, wrap])

Print some string to console.

**String str**: the string value that should be printed

**Boolean wrap**: to print `\n` after printing a string.
  Possible value: true | false
  Default value: true
