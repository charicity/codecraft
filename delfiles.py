import os
import fnmatch
import shutil

def judge(name):
    if(fnmatch.fnmatch(name, '*.cpp')):
        return False
    if(fnmatch.fnmatch(name, '*.h')):
        return False
    if(fnmatch.fnmatch(name, 'CMakeLists.txt')):
        return False
    return True

def traversal(path):
    all_list = []
    file_list = []
    dir_list = []
    del_file = []
    if (os.path.exists(path)==0):
        return

    all_list = os.listdir(path)
    for file in all_list:
        m = os.path.join(path,file)
        if (os.path.isdir(m)==0):
            file_list.append(m)
        else:
            dir_list.append(m)

    for file in file_list:
        if (judge(file)==0):
            continue
        del_file.append(file)
    return dir_list,del_file
        

dirs,files = traversal('./')
print("即将删除的目录：",dirs)
print("即将删除的文件：",files)
answer=input("输入yes继续删除，删除所有其它文件，仅限于提交的时候使用！")
if answer!="yes":
    print("已终止")
    exit()
for dir in dirs:
    shutil.rmtree(dir)
for file in files:
    os.remove(file)
print("已完成")