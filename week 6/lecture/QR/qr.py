import qrcode

img = qrcode.make("https://youtu.be/xvFZjo5PgG0")

img.save("qrcode.png", "PNG")
