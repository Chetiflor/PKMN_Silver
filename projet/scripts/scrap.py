from urllib.request import urlopen
url = "https://www.pokebip.com/page/jeuxvideo/oac/or_argent/liste_attaques"
page = urlopen(url)
html_bytes = page.read()
html = html_bytes.decode("utf-8")
print(html)