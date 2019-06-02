# 명사 및 빈도수 추출과 명사 쓰임 파악, 
# 워드클라우드, SNA를 위한 스크립트


# R언어에서 인덱스는 1부터이므로, 1부터 넣음
social_media <- 1
social_network_service <- 2
sns <- 3
using_data <- sns

line_delimeter_word <- "줄내림"
line_delimeter <- paste(" ", line_delimeter_word, " ", sep="")


words_to_find <- c(line_delimeter_word, "소셜미디어", "한양대", "한류", "무한도전")
words_to_find <- c(words_to_find, "등장", "갈등", "등교", "등산")
words_to_find <- c(words_to_find, "수상", "우수상", "최우수상", "수집")
words_to_find <- c(words_to_find, "교수", "가수", "조회수", "수치", "장수원")
words_to_find <- c(words_to_find, "모바일", "일반", "일본인", "진일보")
words_to_find <- c(words_to_find, "일부", "일상", "만장일치", "러일전쟁")
words_to_find <- c(words_to_find, "일본", "일보", "매일", "일정")
words_to_find <- c(words_to_find, "기적")

words_to_find <- c(words_to_find, "부산파이낸셜뉴스", "이론", "이미지", "이야기", "이사원", "이용", "이어", "상하이")
words_to_find <- c(words_to_find, "페이스북", "인스타그램", "블로그", "트위터", "트윗", "팔로워")
words_to_find <- c(words_to_find, "기기", "개인기", "기자", "기자단")
words_to_find <- c(words_to_find, "대한민국", "한국")
words_to_find <- c(words_to_find, "시도", "서산시", "용인시", "시청", "시킨", "대구시", "광명시")
words_to_find <- c(words_to_find, "샤오미", "빅데이터", "수도", "박명수")


# 최소한 이것은 기본임.
useSejongDic()

mergeUserDic(data.frame(words_to_find, c("ncn")))






get_input_file_name <- function(using_data)
{
  file_name <- switch(using_data, 
                      "Data_OnlySocialMedia2012_2016.txt",
                      "Data_OnlySocialNetworkService2012_2016.txt",
                      "Data_OnlySNS2012_2016.txt"
  )
  return(file_name)
}


get_output_folder_name <- function(using_data)
{
  file_name <- switch(using_data, 
                      "소셜미디어",
                      "소셜네트워크서비스",
                      "SNS"
  )
  return(file_name)
}


input_file_name = get_input_file_name(using_data)
output_folder_name = get_output_folder_name(using_data)


import_all_libraries <- function()
{
  library(descr)
  library(KoNLP)
  library(arules)
  library(igraph)
  library(combinat)
}


erase_duplicated_title_data <- function(data)
{
  return (data[!duplicated(data$V3), ])
}


data_to_title_and_contents <- function(data, delimeter = line_delimeter)
{
  #return (paste(data$V3, delimeter, data$V4))
  return (data$V3)
}


preprocess_contents <- function(contents)
{
  contents <- gsub("&\\w+\\.", "", contents)
  contents <- gsub("<br/>", "", contents)
  
  # 대괄호 같은 특수문자를 지칭할 때는 앞에 \\를 붙여야함
  #contents <- gsub("\\[", line_delimeter, contents)
  
  #숫자 제외, 정규식
  #contents <- gsub("\\d+", " ", contents)
  
  # remove URLs
  contents <- gsub('http[[:alpha:]]*://[[:graph:]]*', ' ', contents)
  
  contents <- gsub("[[:alnum:]]+(\\.[[:alnum:]]+)+", " ", contents)
  
  contents <- gsub("\\.", line_delimeter, contents)
  
  
  # 작은 따옴표, 큰 따옴표 제거
  contents <- gsub("'", "", contents)
  contents <- gsub("\"", "", contents)
  
  # 다른 모양의 따옴표도 제거
  contents <- gsub("‘", "", contents)
  contents <- gsub("’", "", contents)
  contents <- gsub("“", "", contents)
  contents <- gsub("”", "", contents)
  
  
  # 특수문자 모두 제거
  contents <- gsub("[[:punct:]]"," ", contents)
  
  # HTML 태그 제거
  contents <- gsub("(.*>)(.*)(<.*)", "\\2", contents)
  
  
  # 제거할 글자들
  deletions <- c("＜", "＞", "∼", "■", "△", "●", "▲",  "▶",  "▷",   "▦",  "■" )
  deletions <- c(deletions, "◀", "◆", "◇", "◈", "→", "☞", "↓",  "ⓒ")
  for ( i in 1: length(deletions) )
  {
    contents <- gsub(deletions[i], " ", contents)
  }
  
  
  # 2개 이상의 공백을 하나
  #contents <- gsub("\\s+", line_delimeter, contents)
  
  # 2개 이상의 줄내림을 하나
  # \\s?를 써서 사이에 띄어쓰기가 있는 경우와 
  # 없는 경우 모두 포함
  regex_line_delimeter_duplicated <- line_delimeter
  regex_line_delimeter_duplicated <- paste("(\\s?",
                                           line_delimeter,
                                           ")+",
                                           sep="")
  
  contents <- gsub(regex_line_delimeter_duplicated, 
                   line_delimeter, contents)
  
  
  contents <- gsub("(\\S{2,})한", "\\1 ", contents, perl=TRUE)
  contents <- gsub(" 한 ", " ", contents)
  
  
  contents <- gsub(" 등을", " ", contents)
  contents <- gsub(" 등의", " ", contents)
  contents <- gsub(" 등으로", " ", contents)
  contents <- gsub(" 등이다", " ", contents)
  contents <- gsub(" 등과", " ", contents)
  contents <- gsub(" 등에", " ", contents)
  # 1등 2등 할 때 등도 모두 지움
  contents <- gsub(" 등", " ", contents)
  
  contents <- gsub(" 것\\S* ", " ", contents)
  
  
  contents <- gsub("수상작", "수상", contents)
  contents <- gsub(" 수", " ", contents)
  contents <- gsub(" 수가", " ", contents)
  contents <- gsub(" 수만큼", " ", contents)
  contents <- gsub(" 수", " ", contents)
  
  
  contents <- gsub(" 일을 ", " ", contents)
  contents <- gsub(" 일자 ", " ", contents)
  contents <- gsub(" 일일이 ", " ", contents)
  contents <- gsub(" 일할 ", " ", contents)
  contents <- gsub(" 일임할 ", " ", contents)
  contents <- gsub(" 유일하게 ", " ", contents)
  
  
  contents <- gsub(" 흔들리지 ", " ", contents)
  
  contents <- gsub(" (\\S{2,})들\\S* ", "\\1 ", contents, perl=TRUE)
  contents <- gsub(" (\\S{2,})적\\S* ", "\\1 ", contents, perl=TRUE)
  
  
  contents <- gsub(" 이 ", " ", contents)
  contents <- gsub("이를 ", " ", contents)
  contents <- gsub("이번 ", " ", contents)
  
  contents <- gsub("이런 ", " ", contents)
  contents <- gsub("이번 ", " ", contents)
  contents <- gsub("이에 ", " ", contents)
  contents <- gsub("이달 ", " ", contents)
  contents <- gsub(" 이기도 ", " ", contents)
  contents <- gsub(" 이어가며 ", " ", contents)
  
  contents <- gsub(" 이들\\S* ", " ", contents)
  contents <- gsub(" 이라고 ", " ", contents)
  contents <- gsub(" 이라며 ", " ", contents)
  contents <- gsub(" 이라 ", " ", contents)
  
  
  contents <- gsub("(\\S{2,})을 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})를 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})이 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})가 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})에 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})의 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})과 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})는 ", "\\1 ", contents, perl=TRUE)
  
  contents <- gsub("(\\S{2,})해 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})성 ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})하\\S* ", "\\1 ", contents, perl=TRUE)
  contents <- gsub("(\\S{2,})함\\S* ", "\\1 ", contents, perl=TRUE)
  
  
  contents <- gsub(" 기 ", " ", contents, perl=TRUE)
  contents <- gsub(" 를 ", " ", contents, perl=TRUE)
  contents <- gsub(" 을 ", " ", contents, perl=TRUE)
  contents <- gsub(" 중 ", " ", contents, perl=TRUE)
  contents <- gsub(" 위 ", " ", contents, perl=TRUE)
  contents <- gsub(" 일 ", " ", contents, perl=TRUE)
  contents <- gsub(" 의 ", " ", contents, perl=TRUE)
  
  
  contents <- gsub("(\\S{2,})년", " ", contents, perl=TRUE)
  contents <- gsub(" 년\\S*", " ", contents, perl=TRUE)
  
  #contents <- gsub("\\d+\\s*명\\S*", " ", contents, perl=TRUE)
  contents <- gsub("\\d+\\s*일\\S*", " ", contents, perl=TRUE)
  contents <- gsub("\\d+\\s*시\\S*", " ", contents, perl=TRUE)
  contents <- gsub("\\d+\\s*월\\S*", " ", contents, perl=TRUE)
  
  contents <- gsub("무단전재 및 재배포 금지", "", contents)
  contents <- gsub("소셜\\s+미디어", "소셜미디어", contents, perl=TRUE)
  
  return (contents)
}


content_to_article_nouns_list <- function(contents)
{
  # 아래의 것을 전처리에 넣지 않은 이유는,
  # 전처리 된 것을 근거로 문장을 뽑기 때문
  #contents <- gsub(line_delimeter, " ", contents)
  nouns <- sapply(contents, extractNoun, USE.NAMES = F)
  #words <- unlist(nouns, use.name=F)
  
  return (nouns)
}

number_line_to_article_nouns_list <- function(article_nouns_list)
{
  numbered_article_nouns_list <- c()
  for ( i in 1: length(article_nouns_list) )
  {
    line_number <- 1
    one_article_nouns <- article_nouns_list[[i]]
    numbered_one_article_nouns <- c()
    for ( j in 1: length(one_article_nouns) )
    {
      noun <- one_article_nouns[j]
      if ( noun == line_delimeter_word)
      {
        line_number <- line_number + 1
      }
      else
      {
        noun <- paste(line_number, noun, sep = " ") # ' ' 으로 구분
      }
      numbered_one_article_nouns[j] <- noun
    }
    numbered_article_nouns_list[[i]] <- numbered_one_article_nouns
  }  
  
  return (numbered_article_nouns_list)
}

contents_to_sentence_vector_list<- function(contents)
{
  sentence_vector_list <- c()
  for ( i in 1: length(contents) )
  {
    sentence_vector_list[i] <- str_split(contents[i], line_delimeter_word)
  }
  return (sentence_vector_list)
}



extract_sentence_include_one_noun_to_vector <-function(noun, 
                                                       contents,
                                                       article_nouns_list,
                                                       date)
{
  # 여러줄의 텍스트를 한 줄 씩의 원소를 갖는 리스트로 변환함
  # 즉, 리스트를 담는 벡터를 만듬
  sentence_vector_list <- contents_to_sentence_vector_list(contents)
  
  
  numbered_article_nouns_list <- number_line_to_article_nouns_list(article_nouns_list)
  
  
  regex <- paste("^(\\d+) (.+)$", sep="")
  
  
  count <- 0
  # 벡터 선언
  output_sentence_vector <- c()
  # 2차원 벡터 순회
  for ( i in 1: length(numbered_article_nouns_list) )
  {
    # 한 기사 안에 여러 문장을 모아둔 벡터
    one_sentence_vector <- sentence_vector_list[[i]]
    
    not_founded <- TRUE
    
    one_numbered_article_nouns <- numbered_article_nouns_list[[i]]
    for ( j in 1: length(one_numbered_article_nouns) )
    {
      numbered_noun <- one_numbered_article_nouns[j]
      getted_noun <- gsub(regex, "\\2", numbered_noun, perl = TRUE)
      if (getted_noun == noun )
      {
        if (not_founded)
        {
          str_date <- paste(date[i], "", sep="")
          output_sentence_vector <- c(output_sentence_vector, str_date)
          not_founded <- FALSE
        }
        
        line_number <- gsub(regex, "\\1", numbered_noun, perl = TRUE)
        line_number <- as.numeric(line_number)
        
        sentence <- one_sentence_vector[line_number]
        output_sentence_vector <- c(output_sentence_vector, sentence)
        
        count <- count + 1
        if ( count >= 10)
        {
          return (output_sentence_vector)
        }
      }
    }
  }
  
  return (output_sentence_vector)
}


output_sentence_to_file <- function(output_folder_name, 
                                    noun,
                                    sentence_vector)
{
  file_name <- paste("./", output_folder_name, "/", noun , ".txt", sep="")
  separator <- "\r\n\r\n\r\n"
  
  cat(sentence_vector, file = file_name, sep = separator)
}



extract_usage_of_nouns_and_output_file <- function(output_folder_name, 
                                                   words_count, 
                                                   contents,
                                                   article_nouns_list,
                                                   date)
{
  sorted_words_count <- sort(words_count, decreasing=T)
  most_nouns <- names(head(sorted_words_count, 100))
  
  for ( i in 1: length(most_nouns) )
  {
    noun <- most_nouns[i]
    
    if ( noun == line_delimeter_word )
      next;
    
    sentence_vector<-
      extract_sentence_include_one_noun_to_vector(noun, 
                                                  contents,
                                                  article_nouns_list,
                                                  date)
    
    output_sentence_to_file(output_folder_name,
                            noun,
                            sentence_vector)
  }
}

# 단어 빈도수 표를 참조하여, 전처리된 데이터에서 명사의 사용 예시를
# 추출해서 그 폴더의 파일로 저장함.
#extract_usage_of_nouns_and_output_file(output_folder_name,
#                                       words_count, 
#                                       contents_preprocessed,
#                                       article_nouns_list,
#                                       date)


wordcloud <-function(words_count, data_length)
{
  min_freq <- data_length/100
  
  
  if (min_freq < 2)
  {
    min_freq <- 2
  }
  
  
  library(RColorBrewer)
  palete <- brewer.pal(9,"Set1")
  # 노란색과 핑크색, 회색 제거
  palete <- c(palete[1:5], palete[7])
  
  
  try({
#    message <- paste(as.character(min_freq), "\r\n" ,sep="")
#    cat(message)
    bmp(filename="워드클라우드.bmp")
    library(wordcloud)
    wordcloud::wordcloud(names(words_count), freq = words_count, scale = c(8,0.5), rot.per = 0, min.freq = min_freq, random.order = F, random.color = T, colors = palete)
    
  }, silent = T)
  
  dev.off()
}


SNA <- function(sorted_words_count)
{
  sorted_word_first <- names(sorted_words_count[1])
  # line_delimeter_word 제거
  if (sorted_word_first == line_delimeter_word)
  {
    sorted_words_count <- sorted_words_count[2:length(sorted_words_count)]
  }
  
  
  sorted_words_count <- head(sorted_words_count, 20)
  
  sorted_words <- names(sorted_words_count)
  cat(sorted_words, file = "candidate.txt", sep = "\n")
  
  row <- paste(sorted_words, sorted_words_count, sep=",")
  cat(row, file = "candidate_table.csv", sep = "\n")
}


pick_month_data <- function(data, str_year, str_month)
{
  new_data <- data[ which( substr(data$V1, 6, 7)  == str_month & substr(data$V1, 1, 4) == str_year), c("V1", "V2", "V3", "V4")]
  
  return (new_data)
}


create_dir_if_not_exists <- function(dir_name)
{
  main_dir <- "."
  
  if ( ! (file.exists( dir_name ) ) )
  {
    dir.create(file.path(main_dir, dir_name))
  }
}



WC_and_SNA_for_all_months <- function(data)
{
  # 라이브러리 포함
  import_all_libraries()
  
  main_dir <- "."
  
  # 읽어오고, 제목이 중복된 데이터를 모두 제거
  data <- read.delim( input_file_name, header=FALSE )
  data <- erase_duplicated_title_data(data)
  
  
  create_dir_if_not_exists(output_folder_name)
  setwd(file.path(main_dir, output_folder_name))
  
  
  
  years <- c("2011", "2012", "2013", "2014", "2015", "2016")
  months <- c("01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12")
  
  for ( year in years )
  {
    create_dir_if_not_exists(year)
    setwd(file.path(main_dir, year))
    for ( month in months )
    {
      create_dir_if_not_exists(month)
      setwd(file.path(main_dir, month))
      
      WC_and_SNA_for_one_month(data, year, month)
      
      setwd(file.path(main_dir, ".."))
    }
    setwd(file.path(main_dir, ".."))
  }
  
  setwd(file.path(main_dir, ".."))
}



WC_and_SNA_for_one_month <- function(data, str_year, str_month)
{
  data <- pick_month_data(data, str_year, str_month)
  
  data_length <- length(data$V1)
  if (data_length == 0)
  {
    message <- paste(str_year, "년", str_month, "월 데이터 없음", sep="")
    cat(message)
    return()
  }
  else
  {
    
  }
  
  
  # 줄내림(\n)으로 구분하여 제목과 내용을 합칩
  title_and_contents <- data_to_title_and_contents(data, line_delimeter)
  # 전처리
  contents_preprocessed <- preprocess_contents(title_and_contents)
  
  # 각 기사별 명사를 모아둔 리스트
  # 리스트의 각 원소로써, 여러 명사의 벡터가 들어있음
  article_nouns_list <- content_to_article_nouns_list(contents_preprocessed)
  
  # 모든 기사의 명사를 모아서 벡터로 만듬
  words <- unlist(article_nouns_list, use.name=F)
  
  words <- Filter(function(x) {nchar(x) >= 2}, words)   # 두 글자 이상 단어만 저장
  # 전처리된 데이터에서 명사를 추출하여 빈도수 표를 받아옴
  words_count <- table(words)
  words_count[line_delimeter_word]<-0
  words_count[output_folder_name]<-0
  
  
  sorted_words_count <- sort(words_count, decreasing=T)
  
  wordcloud(words_count, data_length)
  SNA(sorted_words_count)
}





WC_and_SNA_for_all_months(data)
