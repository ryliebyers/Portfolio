# Project: Phase 2

```
CREATE TABLE Departments (
    Subject VARCHAR(4) PRIMARY KEY,
    Name VARCHAR(100) NOT NULL   
);
```
```
CREATE TABLE Students (
    uID CHAR(8) PRIMARY KEY,
    fName VARCHAR(100) NOT NULL,
    lName VARCHAR(100) NOT NULL,
    DOB DATE NOT NULL,
    Subject VARCHAR(4) NOT NULL,
    FOREIGN KEY (Subject) REFERENCES Departments(Subject)
);
```
```
CREATE TABLE Professors (
    uID CHAR(8) PRIMARY KEY,
    fName VARCHAR(100) NOT NULL,
    lName VARCHAR(100) NOT NULL,
    DOB DATE NOT NULL,
    Subject VARCHAR(4) NOT NULL,
    FOREIGN KEY (Subject) REFERENCES Departments(Subject)
);
```
```
CREATE TABLE Administrators (
    uID CHAR(8) PRIMARY KEY,
    fName VARCHAR(100) NOT NULL,
    lName VARCHAR(100) NOT NULL,
    DOB DATE NOT NULL
);
```
```
CREATE TABLE Courses (
    Subject VARCHAR(4) NOT NULL,
    Num INT(11) NOT NULL,
    Name VARCHAR(100) NOT NULL,
    PRIMARY KEY (Num, Subject),
    FOREIGN KEY (Subject) REFERENCES Departments(Subject)
);
```
```
CREATE TABLE Classes (
    ClassID INT AUTO_INCREMENT PRIMARY KEY,
    Num INT(11) NOT NULL,
    Year INT(4) UNSIGNED NOT NULL,
    Season ENUM('Spring', 'Summer', 'Fall') NOT NULL,
    Loc VARCHAR(100) NOT NULL,
    Start TIME NOT NULL,
    End TIME NOT NULL,
    ProfessorUID CHAR(8) NOT NULL,
    UNIQUE (Year, Season, Num),
    FOREIGN KEY (Num) REFERENCES Courses(Num),
    FOREIGN KEY (ProfessorUID) REFERENCES Professors(uID)
);
```
```
CREATE TABLE AssignmentCategories (
    CategoryID INT AUTO_INCREMENT PRIMARY KEY,
    ClassID INT NOT NULL,
    Name VARCHAR(100) NOT NULL,
    Weight INT UNSIGNED NOT NULL,
    UNIQUE (Name, ClassID),
    FOREIGN KEY (ClassID) REFERENCES Classes(ClassID)
);
```
```
CREATE TABLE Assignments (
    AssignmentID INT AUTO_INCREMENT PRIMARY KEY,
    CategoryID INT NOT NULL,
    Name VARCHAR(100) NOT NULL,
    Points INT UNSIGNED NOT NULL,
    Content TEXT NOT NULL,
    Due DATETIME NOT NULL,
    UNIQUE (Name, CategoryID),
    FOREIGN KEY (CategoryID) REFERENCES AssignmentCategories(CategoryID)
);
```
```
CREATE TABLE Submissions (
    AssignmentID INT NOT NULL,
    StudentUID CHAR(8) NOT NULL,
    Content TEXT NOT NULL,
    Score INT UNSIGNED,
    Time DATETIME NOT NULL,
    PRIMARY KEY (Time, AssignmentID, StudentUID),
    FOREIGN KEY (AssignmentID) REFERENCES Assignments(AssignmentID),
    FOREIGN KEY (StudentUID) REFERENCES Students(uID)
);
```
```
CREATE TABLE Enrollments (
    StudentUID CHAR(8) NOT NULL,
    ClassID INT NOT NULL,
    Grade CHAR(2),
    UNIQUE (StudentUID, CLassID),
    FOREIGN KEY (StudentUID) REFERENCES Students(uID),
    FOREIGN KEY (ClassID) REFERENCES Classes(ClassID)
);
```