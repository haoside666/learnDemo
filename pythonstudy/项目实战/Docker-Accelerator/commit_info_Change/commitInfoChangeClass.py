
class CommitInfoChange(object):
    _projectName=''
    _commitID=''
    _commitAuthor=''
    _commitDate=''
    _message=''
    _filePath=''
    _changeNum=0

    # def set_projectName(self,projectName):
    #     self._projectName = projectName

    def fill_data_by_dict(self,d):
        self._projectName=d["projectName"]
        self._commitID=d["commitID"]
        self._commitAuthor=d["commitAuthor"]
        self._commitDate=d["commitDate"]
        self._message=d["message"]
        self._filePath=d["filePath"]
        self._changeNum=d["changeNum"]

    def data_to_tuple(self):
        t=(self._projectName,
           self._commitID,
           self._commitAuthor,
           self._commitDate,
           self._message,
           self._filePath,
           self._changeNum)
        return t

