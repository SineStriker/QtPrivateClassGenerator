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

`-a` Add an argument to constructor. (Optional)

`-m` Add a macro at the beginning of class. (Optional)

`-n` Add a namespace before definition. (Optional)

`-o` Specify output directory, the default is current working directory. (Optional)

`-p` Specify project name, it will be used in header definition. (Optional)

`-b` Specify base class name.

`-d` Generate a class derived from a base class, and the base class must be specified.

`-x` Generate private implementations into public class's source file.


### Templates

`--qobject` represents `-a QObject*,parent,nullptr -m Q_OBJECT`

`--qwidget` represents `-a QWidget*,parent,nullptr -m Q_OBJECT`