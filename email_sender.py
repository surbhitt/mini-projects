
#!/usr/bin/env python3

from email.message import EmailMessage
# study the following modules
import ssl
import smtplib

email_sender = 'surbhit.thakur.13744821@gmail.com'
email_password = 'rbrlgabiozuztxet'

email_receiver = 'voh64821@nezid.com'

subject = "this is a trial mail"
body = """
this is the body of a trial mail
this is cool but it would be cooler if i could 
unsubscribe from unnecessary newsletter
""" 

em = EmailMessage()
em['From'] = email_sender
em['To'] = email_receiver
em['subject'] = subject
em.set_content(body)


context = ssl.create_default_context()

with smtplib.SMTP_SSL('smtp.gmail.com', 465, context=context) as smtp:
	smtp.login(email_sender, email_password)
	smtp.sendmail(email_sender, email_receiver, em.as_string())