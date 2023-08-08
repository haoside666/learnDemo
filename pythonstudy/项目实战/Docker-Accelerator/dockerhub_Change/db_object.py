import sys

import pymysql
import logging
import global_config_var
logger = logging.getLogger('my_logger')

class db(object):
    cur = None
    con = None

    def __init__(self):
        try:
            host=global_config_var.mysql_server_ip
            password=global_config_var.mysql_passwd
            user=global_config_var.mysql_user
            if host=="":
                print("mysql_server_ip cannot be empty!!",file=sys.stderr)
                exit(1)
            self.con = pymysql.connect(host=host, password=password, port=3306, user=user,
                                       charset='utf8')
            self.cur = self.con.cursor()
            logger.info("connect success!")
            self.cur.execute("use dockerfile_study")
        except (pymysql.err.OperationalError, pymysql.err.InternalError) as e:
            logger.error("connect fail,error type:"+type(e).__name__)
            if "No route to host" in e.args[1]:
                logger.error("The ip address or the mysql server is incorrect!!")
            elif "Access denied for user" in e.args[1]:
                logger.error("The username or password is incorrect!!")
                logger.error("Please check if your mysql configuration is correct!!")
            else:
                logger.error(e.args[1])
            exit(2)
        except pymysql.Error as e:
            logger.error("throw an exception，type:"+type(e).__name__)
            exit(3)

    def __del__(self):
        if self.cur != None:
            self.cur.close()
        if self.con != None:
            self.con.close()

    def insert_all_data_to_dockerhubChange(self, l):
        try:
            sql = f'insert into dockerhubChange values(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)'
            self.cur.executemany(sql, l)
            self.con.commit()
        except pymysql.DataError as e:
            error_info = e.args[1]
            index = int(error_info[error_info.rfind(" "):])
            l.pop(index - 1)
            while 1:
                try:
                    if l == []: break
                    sql = f'insert into dockerhubChange values(%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s)'
                    self.cur.executemany(sql, l)
                    self.con.commit()
                    break
                except pymysql.DataError as e:
                    a = e.args[1]
                    index = a.rfind(" ")
                    b = a[index:]
                    l.pop(int(b) - 1)
        except:
            raise


if __name__ == "__main__":
    db = db()
    l = []
    t = ('library','python', 1, 'alpine', 2, '3.9.16-alpine3.18', 'add', 'ENV', 'GPG_KEY=A035C8C19219BA821ECEA86B64E628F8D684696D','', 7)
    t1 = ('library','python', 1, 'alpine', 2, '3.9.16-alpine3.18', 'add', 'ENV', 'PYTHON_VERSION=3.11.3', '', 8)
    l.append(t)
    l.append(t1)
    db.insert_all_data_to_dockerhubChange(l)




