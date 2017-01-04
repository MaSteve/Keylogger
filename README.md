# Keylogger
Another C++ keylogger with Mailgun notifications (Still and forever in development)
## Configuration
In order to use this keylogger you should have installed Node v6 and the following npm dependencies previously: 
- node-env-file: `npm install node-env-file`
- mailgun-js: `npm install mailgun-js`

Compile the main file with `g++ keylogger.cpp -w -pthread -o keylogger` and fill in the `.env` file with your own credentials.
Remember to execute the program with superuser permissions (e.g. `sudo ./keylogger`).
