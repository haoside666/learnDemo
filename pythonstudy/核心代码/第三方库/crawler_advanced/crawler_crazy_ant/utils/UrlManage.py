class UrlManage:
    def __init__(self):
        # Pending url
        self.new_url_set = set()
        # Processed url
        self.old_url_set = set()

    def add_url(self, url):
        if url is None or url == "":
            return
        if url in self.new_url_set or url in self.old_url_set:
            return
        self.new_url_set.add(url)

    def add_urls(self, urls):
        if urls is None or len(urls) == 0:
            return
        for url in urls:
            self.add_url(url)

    def get_url(self):
        if self.has_url():
            url = self.new_url_set.pop()
            self.old_url_set.add(url)
            return url

    def has_url(self):
        return len(self.new_url_set) > 0
