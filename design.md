# SDLIB (stands for Super Data LIBrary)

# TOML Specs

## Comments

- Begins at hash symbol and terminates at newline or EOF
- Hash may occur at any point in the line

## Key/Value Pair

Value must be one of the following types:
  string, integer, float, boolean, offset date-time, local date-time, local
  date, local time, array, inline table

Unspecified values are invalid

There must be a newline of EOF after key/value pair

## Keys

Bare keys may only contain A-Za-z0-9_- always interpreted as strings

Quoted keys allow broader set of key names

Dotted keys are a sequence of bare or quoted keys joined with a dot, which
allows for grouping

Whitespace around dot-separated parts is ignored

Indentation is treated as whitespace and ignored

Defining a key *multiple times is invalid*, and bare and quoted keys are
equivalent

As long as a key hasn't been directly defined, you may still write to it, but a
key cannot be redefined as a table

## String

Basic string are surrounded by quotation marks, and characters may be escaped

Multi-line basic strings are surrounded by three quotation marks

A newline immediately after the delimiter is trimmed

A line ending with a backslash will trim to the next non-whitespace character

Literal strings are surrounded by single quotes, in which there is no escaping

Multi-line literal strings are surrounded by three single quotes and allow
newlines

You can write 1 or 2 single quotes anywhere within a multi-line litearl string,
but a sequence of three or more are not permitted

## Integer

Positive numbers may be prefixed with a plus sign

For large numbers you may use underscores between digits, where each underscore
must be surrounded by at least one digit on each side

Leading zeros are not allowed

-0 and +0 are identical to 0

Hexadecimal, octal and binary are prefixed with 0x, 0o and 0b, and are
case-insentive

## Float

Exponent separator may be upper or lower case E

The decimal point, if used, must be surrounded by at least one digit on each
side

Underscores may be used, but follow the same rules as in integer

Special float values may be expressed, but only in lowercase

## Boolean

true or false, always lowercase

## Offset Date-Time

Format: RFC 3339 as described below

Specified syntax description notation:
- date-fullyear = 4DIGIT
- date-month = 2DIGIT
- date-mday = 2DIGIT
- time-hour = 2DIGIT
- time-minute = 2DIGIT
- time-second = 2DIGIT
- time-secfrac = "." 1DIGIT
- time-numoffset = ("+" / "-") time-hour ":" time-minute
- time-offset = "Z" / tim-numoffset
- partial-time = time-hour ":" time-minute ":" time-second [time-secfrac]
- full-date = date-fullyear "-" date-month "-" date-mday
- full-time = partial-time time-offset
- date-time = full-date "T" full-time

"T" may be replaced by space character

date-mday permitted for date-month

```
date-month    date-mday maximum
---------- -----------------
01            31
02 (non-leap) 28
02 (leap)     29
03            31
04            30
05            31
06            30
07            31
08            31
09            30
10            31
11            30
12            31
```

Leap seconds are also considered by the standard

Arguably this library isn't intended as a date sanitiser, so there are no plans
to implement checking algorithms beyond simple bounds tests

## Local Date-Time

RFC 3339 with timezone omitted

## Local Data

Date portion RFC 3339

## Local Time

Time portion RFC 3339

## Array

Square brackets containing comma-separated values

Whitespace is ignored

Values of different types may be mixed (C++ restrictions will have to apply
here)

Arrays may span multiple lines

Trailing commas are allowed even after the last element

## Table

Defined by headers, with square brackets on a line by themselves

All followed key/value pairs belong to this table, until the next header or EOF

Naming rules for tables are the same as for keys

Empty tables are allowed

Dotted key names define tables, so redefining them with headers is not allowed

```
[table]
key = "value"
```

## Inline Table

Collection of key/value pairs within curly braces on a single line

As such, newlines are not permitted, unless within the parsing for a value type

## Array of Tables

Table name within double brackets, where each table definition is a new element
within the array

Dotted references to an array of tables points to the most recently defined
table element

```
[[users]]
name = "Frost Noser"
dob = 1987-03-16

[[users]]
name = "Ankle Biter"
dob = 2002-01-06
```

# Implementation Specific

## Old Implementation Details

Handling data storage
- Each value is stored within a type anonymous struct (implented via union) that
  also contains an identifier for the type of its storage
- Value objects are stored within an allocated buffer, with a static buffer
  being used to optimise reading small files
- Keys are stored as a tuple [id: string, typeId: data_type_id, offset: [start:
  long, end: long]]
- Key tuples are stored within a allocated sorted buffer, with a static buffer
  being used to optimise reading small files
- Key names are expanded to their full table identifier from the root table (see
  Example 1)
- Arrays of tables and inline tables are parsed as value objects with a Table
  data type
- Key names are stored in shortened form if member of previous table (see
  Example 2)

Example 1:
```
[Table]
baseKey = 12
key.subKey = 34

Generates the following key identifiers:
Table
Table.baseKey
Table.key
Table.key.subKey
```

## IMPORTANT DETAIL

- Try to encode as much as you can in UTF-8

## Tokenising

1. Determine table header, table array header or key/value pair
2. Parse key as string
3. Check for key in hash map (error if it exists, because keys shouldn't be
  redefined)
4. Parse value as value type\*
5. Insert key/value pair in hash map

\* see below

- For dotted keys, all possible parent key names should also be appended to the
  hash map as empty values
- Inline tables are appended as empty values, with each table key being parsed
  in order

## Building Hash Map

- Hash map nodes contain a key/value pair parsed from input as well as a pointer
  to the next node in the linked list "bucket"
- Hash map specifies how many "buckets" it contains and a reference to a hashing
  function
- When inserting, the key is hashed and the appropriate "bucket" is checked; if
  there is a collision, the key/value pair is appended to the end of the linked
  list
- Due to the nature of this hash map implementation, deleting keys isn't
  considered relevant
- Keys may not be modified

## Memory Allocation

- The API should expose allocator detail, similar to standard library containers
- Therefore, allocator detail should be implemented according to the standard
  library
  - This provides familiarity as well as good defaults for those who don't need
    this level of control
- By default, the library uses global `::new` and `::delete` operators for the
  default allocators for all associated value types
  - This can be modified to use pmr allocators to improve performance, but that
    is outside the scope of this library and my interest in it
- Some keys reference arrays, which are stored as array types values, pointing
  to a contiguous buffer of values with a specified length

## Parsing Values

