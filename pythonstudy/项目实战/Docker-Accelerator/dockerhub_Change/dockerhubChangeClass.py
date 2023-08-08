class DockerhubChange(object):
    _namespace = ''
    _repository = ''
    _newTagID = 0
    _newTag = ''
    _oldTagID = 0
    _oldTag = ''
    _mType = ''
    _cmd = ''
    _cmdArgv = ''
    _addition = ''
    _changeNum = 0


    def fill_data_by_dict(self, d):
        self._namespace = d["namespace"]
        self._repository = d["repository"]
        self._newTagID = d["newTagID"]
        self._newTag = d["newTag"]
        self._oldTagID = d["oldTagID"]
        self._oldTag = d["oldTag"]
        self._mType = d["mType"]
        self._cmd = d["cmd"]
        self._cmdArgv = d["cmdArgv"]
        self._addition = d["addition"]
        self._changeNum = d["changeNum"]


    def data_to_tuple(self):
        t = (self._namespace,
             self._repository,
             self._newTagID,
             self._newTag,
             self._oldTagID,
             self._oldTag,
             self._mType,
             self._cmd,
             self._cmdArgv,
             self._addition,
             self._changeNum)
        return t
