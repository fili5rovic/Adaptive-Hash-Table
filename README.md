# Adaptive Hash-Table

The Adaptive Hash Table is an innovative data structure project designed to provide efficient data storage and retrieval by dynamically adjusting its hashing mechanisms based on the data characteristics and load factors. This project aims to improve upon traditional hash table implementations by increasing performance and reducing collision rates in varying scenarios.


This project uniquely demonstrates the distinction between an Adaptive Hash Table and a traditional HashTable by providing comprehensive statistics for both, allowing users to clearly observe and compare their performance metrics. Project aims to showcase the efficiency and adaptability of the Adaptive Hash Table in various data handling scenarios.
> The main objective of this project was to gain hands-on experience with Adaptive HashTables and specifically explore the implementation of operations like inserting and deleting elements, resolving collisions through quadratic hashing and maintaining the table's efficiency.
> 
> This project was developed as the [third university assignment](instructions.pdf) for "Algorithms and Data Structures 2" at the University of Belgrade School of Electrical Engineering majoring in Software Engineering. Please refer to the file for detailed assignment instructions.

## Table of Contents

- [Features](#features)
  - [Hash Table Operations](#hash-table-operations)
  - [Collision resolution](#collision-resolution)
  - [Adaptive Hash Table](#adaptive-hash-table)
  - [Performance Evaluation](#performance-evaluation)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Usage](#usage)
- [File Format](#test-file-format)

## Features

### Hash Table Operations

The conceptual class diagram is shown in the following image:
![diagram](https://github.com/fili5rovic/Adaptive-Hash-Table/assets/110270696/405321d6-c7a4-4b48-9e44-544c39f4ce65)




By the given instructions, these next functions are implemented:

| Function | Description |
|---|---|
| `findKey(Key k)` | Returns a pointer to the string associated with the key, or 0 if not found. |
| `insertKey(Key k, string s)` | Inserts a key with its string into the table and reports status. |
| `deleteKey(Key k)` | Removes a key from the table, returning the operation status. |
| `avgAccessSuccess()` | Gives the average successful key search access count. |
| `avgAccessUnsuccess()` | Calculates average accesses for failed key searches. |
| `resetStatistics()` | Resets all access counting data for average calculation. |
| `clear()` | Eliminates all table data. |
| `keyCount()` | Reports the total count of inserted keys. |
| `tableSize()` | Provides the current table size. |
| `operator<<` | Outputs the table contents or "EMPTY" for unoccupied entries. |
| `fillRatio()` | Returns the table's fill ratio between 0 and 1. |


## Collision resolution
The class representing the abstraction of the address function that the HashTable will use for resolving collisions is specified to the hash table object during its creation.
This abstract class defines the interface for the address function used by a hash table to resolve collisions. The HashTable must provide an object of this class during its creation.

```
Address getAddress(Key k, Address a, Attempt i) 
```

Parameters:
- `k`: Key.
- `a`: Base address.
- `i`: Attempt number of access.

This method returns a new address where the key should be looked for. 

Derived class `QuadraticHashing` specifies how to determine the next address.

### Quadratic Hashing Class
The Quadratic Hashing class is parameterized by the values of `c1` and `c2` and returns the following value:

```
return address + attempt * c1 + attempt * attempt * c2;
```

## Adaptive Hash Table
HashTable has an adaptive and a standard mode, which can be chosen by the user. Adaptive HashTable automatically adjusts its size based on load factors and average access counts.

## Performance Evaluation
A performance evaluation of a hash table is performed by inserting the given keys (in a specified range of values) into a given HashTable and then generating a specified number of keys of **pseudorandom** values and performing a search on them. After that, the results (average number of accesses in a **successful** search and calculated number of accesses in an **unsuccessful** search) are printed.<br />

The range in which random numbers are generated is determined so that it corresponds to the range of values of the keys inserted into the table (in this case these numbers are between minimum and maximum key in "[DZ3_Recnik_10K.txt](Files/DZ3_Recnik_10K.txt)" file.

## Getting Started

### Prerequisites
Before you begin, ensure you have the following prerequisites:

- C++ Compiler: Make sure you have a C++ compiler installed on your system.
- Ensure that your terminal supports ASCII escape codes to view the colorized and formatted output correctly.

### Compilation and Execution

1. Ensure you have a C++ compiler installed.
2. Clone this repository.
3. Navigate to the directory containing the source code.
4. Compile the code.
5. Run the compiled program.

 ### Usage

Upon execution, the program presents a menu with various options, as explained in [Features](#features) section, to interact with the user. Follow the on-screen prompts to perform operations.


## Test File format
When creating new test files, the format should be as follows:
```
<value> <\t> <key>
```
* **value** is of type *string*
* **\t** represents a *tab* between value and key 
* **key** is of type *long int*

This project includes 2 test files, named [`mytest.txt`](Files/mytest.txt) and [`DZ3_Recnik_10K.txt`](Files/DZ3_Recnik_10K.txt) (main file given by faculty).
