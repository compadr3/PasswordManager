# PasswordManager

C++ password manager
PasswordManager stores: name, password, category, website and login.

Data is encrypted using XOR logical operator on user password and data. E.g: password ^ data

To choose a file that you want to access you can input one of PasswordManager files that are already in program folder, or you can provide absolute path.

To create new PasswordManager file you have to provide absolute path to it, then u will be asked to create password to a
file.

PM commands:
1. find - find data in file
2. sort - sort data in file
3. add - add data to file
4. edit - edit data in file
5. delete - delete data in file
6. add-category - add category to file
7. delete-category - delete category from file
8. print - print data from file
9. commands - print commands
10. exit - exit program