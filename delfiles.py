answer=input("输入y继续删除，删除所有其它文件，仅限于提交的时候使用！")
if answer!="y":
    exit()


def get_files():
    for filepath,dirnames,filenames in os.walk(r'E:\test2'):
        for filename in filenames:
            print(os.path.join(filepath,filename))
