import smtplib
import email.mime.text

passwd = "tony19841211%" # TODO remove me when you submit

# TODO add prompts add the rest of the prompts

# prompt for "from"
emailfrom = input("From: ")
# prompt for "to"
emailto = input("To: ")
# prompt for "subject"
subject = input("Subject: ")

msg = input("Enter message: ")

try:
       # create the email
       mail = email.mime.text.MIMEText(msg)

       mail["From"] =  emailfrom # TODO fill me in with the information from input
       mail["To"] = emailto # TODO fill me in with the information from input
       mail["Subject"] = subject # TODO fill me in with the information from input

       server = smtplib.SMTP_SSL("smtp.gmail.com", port=465)
       server.set_debuglevel(False)
       server.login("""tiancao@cs.unc.edu""", passwd)

       try:
           server.send_message(mail)
           server.quit()

       finally:
           server.close()

except smtplib.SMTPAuthenticationError:
    print("Your password was incorrect.")