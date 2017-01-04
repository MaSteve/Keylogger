# Keylogger
Another C++ keylogger with Mailgun notifications (Still and forever in development)
## Configuration
In order to use this keylogger you should have installed Node v6 and the following npm dependencies previously: 
- node-env-file: `npm install node-env-file`
- mailgun-js: `npm install mailgun-js`

Compile the main file with `g++ keylogger.cpp -w -pthread -o keylogger` and fill in the `.env` file with your own credentials.

Remember to execute the program with superuser permissions (e.g. `sudo ./keylogger`).

You can also use the `launcher.sh` file as long as you have superuser permissions, but, once you execute it, you only can stop the program using `kill PID`, where `PID` is the keylogger process identifier. You can obtain the `PID` value with the following command: `ps aux | grep 'keylogger'`.

By default, the program will try to notify the user activity each hour sending an email. You can modify this behaviour changing the `TIMEOUT` value in `keylogger.cpp` and the parameters in the `.env` file.

This program only works in some Linux distros. Maybe, you will need to modify the `KEYBOARDFILE` constant value in `keylogger.cpp` depending on the computer where it will be executed.

Enjoy it!
