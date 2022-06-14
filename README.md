# Qt Private Class Generator

Simple command line tool to generate c++ source files with Qt private class template.

## Requirements

Only standard libraries are used, no platform limit.

## Examples

### Generate Sample Files

````
qtpcgen -p project -a int,i,0 -b Object Base
````

Then you can generate `Base` and `BasePrivate` files.

````
qtpcgen -p project -d -a int,i,0 -b Base Derived
````

Then you can generate `Derived` and `DerivedPrivate` files.

### Usage

`-a` tells generator to add an argument to constructor. (Optional)

`-m` tells generator to add a macro at the beginning of class. (Optional)

`-o` tells generator the output directory, the default is current working directory. (Optional)

`-p` tells generator the project name, it will used in header definition. (Optional)

`-b` tells generator the base class name.

`-d` tells generator that the private class is derived from a base class, and the base class must be specified.

### Templates

`--qobject` represents `-a QObject*,parent,nullptr -m Q_OBJECT`

`--qwidget` represents `-a QWidget*,parent,nullptr -m Q_OBJECT`