import re
import os
def mkdir_if_not_exist(folder_name):
    if not os.path.isdir(folder_name):
        os.mkdir(folder_name)


def file_to_list(filename):
    file_candidate = open(filename, "r")
    list_candidate = []

    for line in file_candidate:
        line = line.rstrip()
        list_candidate.append(line)

    file_candidate.close()

    return list_candidate


def count_coexists(list_articles, word1, word2):
    count = 0

    dir_name = word1+"-"+word2
    mkdir_if_not_exist(dir_name)
    os.chdir(dir_name)

    # 한 기사안에 동시에 들어가는 것을 확인
    regex = "(" + word1 + ".*" + word2 + ")|(" + word2 + ".*" + word1 + ")"
    for article in list_articles:
        if bool(re.search(regex, article)) == True :
            count = count + 1

            if count > 3:
                continue
            
            # 두 단어가 한 기사에 동시에 들어간다면, 그 기사를 파일로 내보냄
            list_one_article = article.split("\t")
            file_name = list_one_article[0] + " " + list_one_article[2] +".html"
            regex_for_file = "[(\\)(/)(\")(\?)(\|)(<)(>)(\*)(\:)]"
            file_name = re.sub(regex_for_file, ' ', file_name)
            file = open(file_name, "w")
            file.write(list_one_article[3])
            file.close()
            

    os.chdir("..")
    return count



folder_name = "소셜미디어"
edge_list_folder_name = "edge list"
range_name1 = "200-"
range_name2 = "150-200"
range_name3 = "100-150"
range_name4 = "50-100"
range_name5 = "0-50"





def make_all_directories_if_not_exists():
    mkdir_if_not_exist(folder_name)
    os.chdir(folder_name)
    mkdir_if_not_exist(edge_list_folder_name)
    #mkdir_if_not_exist(range_name1)
    #mkdir_if_not_exist(range_name2)
    #mkdir_if_not_exist(range_name3)
    #mkdir_if_not_exist(range_name4)
    #mkdir_if_not_exist(range_name5)
    os.chdir("..")



# 코드는 여기서부터 실행됩니다.


list_tweet = file_to_list("Data_OnlySocialMedia2012_2016.txt")


make_all_directories_if_not_exists()
os.chdir(folder_name)

list_candidate = file_to_list("candidate.txt")

out_file_200 = open("./" + edge_list_folder_name + "/" + range_name1 + ".csv", "w")
out_file_150_200 = open("./" + edge_list_folder_name + "/" + range_name2 + ".csv", "w")
out_file_100_150 = open("./" + edge_list_folder_name + "/" + range_name3 + ".csv", "w")
out_file_50_100 = open("./" + edge_list_folder_name + "/" + range_name4 + ".csv", "w")
out_file_0_50 = open("./" + edge_list_folder_name + "/" + range_name5 + ".csv", "w")

#print(list_tweet)

# 여기서 리스트를 만듬
for word1 in list_candidate:
    for word2 in list_candidate:
        if word1==word2 or word1=="기자" or word2=="기자":
            continue
        else:
            count = count_coexists(list_tweet, word1, word2)
            line = word1 + "," + word2 + "," + str(count) + "\n"

            if count > 200:
                out_file_200.write(line)
            elif count > 150:
                out_file_150_200.write(line)
            elif count > 100:
                out_file_100_150.write(line)
            elif count > 50:
                out_file_50_100.write(line)
            else:
                out_file_0_50.write(line)

os.chdir("..")            
out_file_200.close()
out_file_150_200.close()
out_file_100_150.close()
out_file_50_100.close()
out_file_0_50.close()


# 파일 쓰기 하면 끝
