
class GitChange(object):
    _pAddress=''
    _rAddress=''
    _newCommitID=0
    _newCommit=''
    _oldCommitID=0
    _oldCommit=''
    _mType=''
    _cmd=''
    _cmdArgv=''
    _addition=''
    _commitNum=0

    def set_pAddress(self,pAddress):
        self._pAddress = pAddress

    def set_cmdArgv(self,cmdArgv):
        self._cmdArgv = cmdArgv

    def fill_data_by_dict(self,d):
        self._rAddress=d["rAddress"]
        self._newCommitID=d["newCommitID"]
        self._newCommit=d["newCommit"]
        self._oldCommitID=d["oldCommitID"]
        self._oldCommit=d["oldCommit"]
        self._mType=d["mType"]
        self._cmd=d["cmd"]
        self._cmdArgv=d["cmdArgv"]
        self._addition=d["addition"]
        self._commitNum=d["commitNum"]

    def data_to_tuple(self):
        t=(self._pAddress,
           self._rAddress,
           self._newCommitID,
           self._newCommit,
           self._oldCommitID,
           self._oldCommit,
           self._mType,
           self._cmd,
           self._cmdArgv,
           self._addition,
           self._commitNum)
        return t

