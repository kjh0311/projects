
# 월별 뉴스기사 뽑아내는 절차


# 1. 월별 뉴스기사 뽑아내기 폴더를 만든다.

# 2. 그 안에 소셜미디어, 소셜네트워크서비스, SNS폴더를 만듬


# 각 폴더에 대해서 다음과 같은 작업을 함

# 1. 그 안에 제목 뽑아내기 폴더를 만든다.

# 2. 제목 뽑아내기 폴더에 몇월.txt 파일을 월별로 만든다.

# 3. 상위 폴더로 돌아가서,
#    그 안에 기사 뽑아내기 폴더를 만든다.

# 4. 기사 뽑아내기 폴더에 몇월 폴더를 만든다.

# 5. 각 월별 폴더에, (몇 일, 제목).html 파일을 만든다.



import os
import re


top_folder_name = '월별 뉴스기사 뽑아내기'
file_names = {'소셜미디어':'Data_OnlySocialMedia2012_2016.txt', \
            '소셜네트워크서비스':'Data_OnlySocialNetworkService2012_2016.txt',\
            'SNS':'Data_OnlySNS2012_2016.txt'}
title_folder_name = '제목 뽑아내기'
article_folder_name = '기사 뽑아내기'


def program_start():
    # 1. 월별 뉴스기사 뽑아내기 폴더를 만든다.
    mkdir_if_not_exist(top_folder_name)
        
    os.chdir(top_folder_name)

    extract_monthly_article(file_names, '소셜미디어')
    extract_monthly_article(file_names, '소셜네트워크서비스')
    extract_monthly_article(file_names, 'SNS')    
    
    os.chdir("..")


def extract_monthly_article(file_names, folder_name):

    # 파일을 모두 읽어서 lines에 저장함
    lines = file_to_lines("../"+file_names[folder_name])

    mkdir_if_not_exist(folder_name)
    os.chdir(folder_name)
    
    # 제목만 뽑아서 .txt파일로
    title_to_text_file(lines)
    # 기사를 .html파일로
    article_to_html(lines)       

    os.chdir("..")


def title_to_text_file(lines):
    mkdir_if_not_exist(title_folder_name)
    os.chdir(title_folder_name)

    make_year_folders_if_not_exists()


    prev_month = ""
    file = ""


    i = 0
    while i < len(lines):
        line = lines[i]
        listed_line = line.split("\t")
        date = listed_line[0]
        press = listed_line[1]
        title = listed_line[2]

        
        listed_date = date.split(".")

        year = listed_date[0]
        month = listed_date[1]
        month = month_to_2digit(month)

        os.chdir(year)

        if prev_month != month:
            try:file.close()
            except:pass            
            file = open(month+"월.txt", "w")
            prev_month = month

        file.write(date + " " + press + " " + title + "\n")
        
        os.chdir("..")
        i = i + 1
    


    os.chdir("..")
    

def article_to_html(lines):
    mkdir_if_not_exist(article_folder_name)
    os.chdir(article_folder_name)

    make_year_and_month_folders_if_not_exists()


    for line in lines:
        listed_line = line.split("\t")
        date = listed_line[0]
        title = listed_line[2]        
        content = listed_line[3]

        if title.find(";") != -1:
            title, content = title.split(";", 1)
        
        listed_date = date.split(".")

        year = listed_date[0]
        month = listed_date[1]
        month = month_to_2digit(month)


        os.chdir(year)
        os.chdir(month)

        file_name = date + ' ' + title + '.html'
        regex = "[(\\)(/)(\")(\?)(\|)(<)(>)(\*)(\:)]"
        file_name = re.sub(regex, ' ', file_name)
        #print(file_name)
        try:
            if not os.path.isfile(file_name):
                file = open(file_name, "w")
                file.write(content)
                file.close()
        except:
            print(file_name)
            exit()
        
        
        os.chdir("..")
        os.chdir("..")


    os.chdir("..")



def make_year_folders_if_not_exists():
    for year in range(2011, 2017):
        str_year = str(year)
        mkdir_if_not_exist(str_year)        
    


def make_year_and_month_folders_if_not_exists():
    for year in range(2011, 2017):
        str_year = str(year)
        mkdir_if_not_exist(str_year)
        os.chdir(str_year)
        for month in range(1,13):
            str_month = str(month)
            str_month = month_to_2digit(str_month)
            mkdir_if_not_exist(str_month)
            
        os.chdir("..")

def month_to_2digit(str_month):    
    if len(str_month) < 2:
        str_month = "0" + str_month
    return str_month
        

def file_to_lines(file_name):
    file = open(file_name, "r")
    lines = file.readlines()
    file.close()
    return lines

    
def mkdir_if_not_exist(folder_name):
    if not os.path.isdir(folder_name):
        os.mkdir(folder_name)


program_start()





