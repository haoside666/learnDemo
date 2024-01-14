class RequestContentExcept(Exception):
    def __init__(self, message='ParseError'):
        super().__init__(message)
