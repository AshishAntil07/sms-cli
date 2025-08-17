# Student Management System CLI

[![Release](https://github.com/AshishAntil07/sms-cli/actions/workflows/release.yml/badge.svg)](https://github.com/AshishAntil07/sms-cli/actions/workflows/release.yml)
![Language](https://img.shields.io/badge/Language-C-blue.svg)
![Version](https://img.shields.io/badge/Version-1.0.0-green.svg)
![License](https://img.shields.io/badge/License-MIT-yellow.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows%20%7C%20macOS-lightgrey.svg)
![Build](https://img.shields.io/badge/Build-Make-orange.svg)

A command-line interface for managing and monitoring student data.

## Introduction

**SMS CLI** is a powerful, lightweight command-line application written in C that provides comprehensive student management capabilities. Built with performance and simplicity in mind, this tool offers a robust solution for educational institutions, tutors, and administrators who need to efficiently manage student records without the overhead of complex GUI applications.

The application leverages CSV-based data storage for portability and compatibility, while providing advanced features like data filtering, bulk operations, and flexible record management. With its modular architecture and comprehensive test suite, SMS CLI is designed to be both reliable and extensible.

## Features

### Core Management Operations

- **Student Registration**: Add individual students with complete profile information
- **Bulk Import**: Import multiple student records from CSV files with automatic data validation
- **Record Updates**: Modify student information using property-specific flags
- **Student Removal**: Delete single or multiple student records efficiently
- **Advanced Listing**: Display students with filtering and range-based queries

### Data Management

- **CSV Integration**: Native support for CSV import/export operations
- **Data Persistence**: Automatic data storage in structured CSV format
- **Property-based Filtering**: Search and filter students by any attribute
- **Range Queries**: Filter students by roll number ranges
- **Data Validation**: Built-in validation for data integrity

### Developer Features

- **Comprehensive Testing**: Full test suite with automated validation
- **Cross-platform Support**: Compatible with Linux, Windows, and macOS
- **Memory Management**: Efficient memory allocation and cleanup
- **Modular Architecture**: Clean separation of concerns for easy maintenance

## Problem it Solves

Educational institutions often struggle with efficient student data management, especially when dealing with:

### Current Challenges

- **Manual Record Keeping**: Time-consuming paper-based or spreadsheet management
- **Data Inconsistency**: Lack of standardized data entry and validation
- **Limited Search Capabilities**: Difficulty in finding specific student records quickly
- **Bulk Operations**: Challenges in handling large datasets efficiently
- **Data Portability**: Problems with data transfer between different systems

### SMS CLI Solutions

- **Streamlined Operations**: Quick command-line access to all student management functions
- **Standardized Data Format**: Consistent CSV-based storage with validation
- **Powerful Search & Filter**: Advanced querying capabilities with multiple criteria
- **Bulk Processing**: Efficient handling of large student datasets
- **Universal Compatibility**: CSV format ensures data portability across platforms

### Future Potential

With continued development, SMS CLI can evolve to include:

- **Academic Records**: Integration with grading and attendance systems
- **Reporting & Analytics**: Comprehensive student performance analysis
- **Multi-institutional Support**: Management across multiple campuses or departments
- **API Integration**: RESTful API for web application integration
- **Advanced Security**: Role-based access control and data encryption
- **Cloud Synchronization**: Remote data backup and multi-device access

## Project Tree

```
sms-cli
├─ LICENSE
├─ Makefile
├─ README.md
├─ config.h
├─ inc
│  ├─ cmd
│  │  ├─ about.h
│  │  ├─ add.h
│  │  ├─ help.h
│  │  ├─ index.h
│  │  ├─ list.h
│  │  ├─ remove.h
│  │  └─ update.h
│  ├─ index.h
│  ├─ lib.h
│  ├─ tests
│  │  └─ index.h
│  └─ utils
│     ├─ utils.h
│     └─ vec.h
├─ src
│  ├─ cmd
│  │  ├─ about.c
│  │  ├─ add.c
│  │  ├─ help.c
│  │  ├─ index.c
│  │  ├─ list.c
│  │  ├─ remove.c
│  │  └─ update.c
│  ├─ init.c
│  ├─ lib.c
│  ├─ main.c
│  └─ utils
│     ├─ utils.c
│     └─ vec.c
└─ tests
   ├─ index.c
   ├─ lib.test.c
   └─ vec.test.c
```

## Installation

### For Contributors (Development Setup)

1. **Clone the repository:**

```bash
git clone https://github.com/AshishAntil07/sms-cli.git
cd sms-cli
```

2. **Build the project:**

```bash
make
```

3. **Run tests:**

```bash
make test-neat
```

4. **Clean build files:**

```bash
make clear
```

### For End Users (CLI Installation)

1. **Download and build:**
    - Go to the [latest release](https://github.com/AshishAntil07/sms-cli/releases/latest)  
    - Download the `sms` file from **Assets**.

2. **Add to PATH (Linux/macOS):**

```bash
sudo cp ~/Downloads/sms /usr/local/bin/
```

3. **Add to PATH (Windows):**

```cmd
copy %HOMEPATH%\Downloads\sms C:\Windows\System32\
```

4. **Verify installation:**

```bash
sms about
```

## Usage

### Basic Commands

#### Show Help

```bash
sms help                    # Show all available commands
sms help <command>          # Show detailed help for specific command
```

#### Add Students

```bash
# Add single student
sms add <roll> <name> <gender> <phone> <email> <f_name> <m_name> <address>

# Import from CSV file
sms add <csv_file>
sms add --csv <csv_file>
```

#### List Students

```bash
# List all students
sms list

# Filter by property
sms list --name "John Doe"
sms list --gender M --address Chandigarh,\ Sector\ 17
sms list --phone "123-456-7890"

# Filter by roll number range
sms list --roll 240130800001 240130800096
```

#### Export Student List

```bash
# Export all students
sms list --export path/to/file.csv

# Export filtered students
sms list --gender M --export path/to/file.csv --roll 230130800001 230130824025 --export path/to/another/file.csv
```

#### Update Student Information

```bash
sms update <roll> --name "New Name" --phone "New Phone"
sms update <roll> --email "new@email.com" --address "New Address"
```

#### Remove Students

```bash
sms remove <roll>              # Remove single student
sms remove <roll1> <roll2>...  # Remove multiple students
```

#### Application Information

```bash
sms about                   # Show application information and version
```

### Property Flags

Available properties for update and filtering:

- `--name`: Student full name
- `--roll`: Roll number
- `--gender`: Gender (M/F)
- `--phone`: Phone number
- `--email`: Email address
- `--f_name`: Father's name
- `--m_name`: Mother's name
- `--address`: Address

### CSV Format

The application uses the following CSV structure:

```csv
roll,name,gender,phone,email,f_name,m_name,address
240130800001,"John Doe",M,"123-456-7890","john@example.com","Father Name","Mother Name","123 Street, City"
```

## License

This project is licensed under the MIT License - see the [`LICENSE`](LICENSE) file for details.

**Copyright (c) 2025 Ashish Antil**
