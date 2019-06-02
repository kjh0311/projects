package eml_parser;
import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Properties;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import javax.mail.BodyPart;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.internet.MimeUtility;
import com.sun.mail.util.BASE64DecoderStream;


public class FileTester{
	private static final String 
	//SRC_DIR = "극지에서 온 eml",
	SRC_DIR = "alaska_2017",
	//EXTRACTED_SBD_FILES_DIR = "sbd 파일 모음",
	EXTRACTED_SBD_FILES_DIR = "2017-08-16 sbd 파일 모음",
	DST_FILENAME = "수집된 데이터.csv",
	UTF8_BOM = "\uFEFF",
	COLUMN_HEADER = "파일 이름,날짜/시간,첨부 파일\n",
	ROW_FORMAT = "%s,%s",
	DIR_NOT_FOUND = " 폴더가 없음",
	DATE_AND_TIME_PATTERN = "Time of Session \\(UTC\\): (.+)",
	FILE_SIZE_PATTERN = "size=(\\d+);";
	
	
	
	public static void main(String[] args) throws IOException, MessagingException{
		new FileTester();
	}
	
	
	private FileTester() throws IOException, MessagingException{
		File extracted_sbd_files_dir, src_dir, files[];		
		
		
		extracted_sbd_files_dir = new File(EXTRACTED_SBD_FILES_DIR);
		if (extracted_sbd_files_dir.exists() == false){
			extracted_sbd_files_dir.mkdir();
		}
		
		
		src_dir = new File(SRC_DIR);
		files = src_dir.listFiles();		
		if (files == null){
			System.out.println(SRC_DIR+DIR_NOT_FOUND);
		}else{			
			Session mail_session;
			BufferedWriter writer;			
			mail_session = getMailSession();
			writer = new BufferedWriter(new FileWriter(DST_FILENAME));
			writer.write(UTF8_BOM+COLUMN_HEADER);			
			for (int i = 0; i < files.length; i++){
			//for (int i = 0; i < 1; i++){
				File file;
				String file_name;
				FileInputStream source;
				MimeMessage message;
				Object content;
				file = files[i];
				file_name = file.getName();
				source = new FileInputStream(file);	
				message = new MimeMessage(mail_session, source);
				content = message.getContent();
				write_information_and_save_attachment(writer, file_name, content);				
			}			
			writer.close();
		}
	}
	
	
	private void write_information_and_save_attachment(BufferedWriter writer, String file_name, Object content) throws MessagingException, IOException{		
		if(content instanceof MimeMultipart){
			// 첨부파일이 있는 경우
			//System.out.println("첨부파일이 있는 경우");
			MimeMultipart multipart = (MimeMultipart)content;			
			write_information_and_save_attachment_in_multipart(writer, multipart, file_name);					
		}else{
			// 첨부파일이 없는 메일은 이렇게 기록만 함.
			String text;
			String date_and_time;	
			text = (String)content;
			date_and_time = get_data_by_regex(text, DATE_AND_TIME_PATTERN);			
			writer.write(String.format(ROW_FORMAT, 
						file_name, date_and_time));
		}
		writer.write("\n");
	}	
	

	private void write_information_and_save_attachment_in_multipart(BufferedWriter writer, MimeMultipart multipart, String file_name) throws IOException, MessagingException {		
		for (int i=0; i<multipart.getCount(); i++){
			MimeBodyPart bodypart;
			String content_type;			
			bodypart = (MimeBodyPart) multipart.getBodyPart(i);
			content_type = bodypart.getContentType().split("/")[0];			
			if (content_type.equals("text")){
				String text, date_and_time;				
				text = (String) bodypart.getContent();
				date_and_time = get_data_by_regex(text, DATE_AND_TIME_PATTERN);				
				if (date_and_time!=null){
					writer.write(String.format(ROW_FORMAT, 
							file_name, date_and_time));
				}
			}else if(content_type.equals("application")){
				//System.out.println("save_attachment");
				write_attachment_filename_and_save(writer, bodypart);
			}
		}
	}
	
	
	private void write_attachment_filename_and_save(BufferedWriter writer, MimeBodyPart bodypart) throws MessagingException, IOException {			
		String attachment_filename, attachment_filepath;		
		int file_size, file_size_limit;
		byte[] attachment_buffer;
		BASE64DecoderStream decoder_stream;
		attachment_filename = MimeUtility.decodeText(bodypart.getFileName());
		writer.write(","+attachment_filename);
		
		attachment_filepath = String.format("%s/%s",
											EXTRACTED_SBD_FILES_DIR,
											attachment_filename);
		
		file_size_limit = bodypart.getSize();
		attachment_buffer = new byte[file_size_limit];
		decoder_stream = (BASE64DecoderStream) bodypart.getContent();
		file_size = read(attachment_buffer, decoder_stream);
        save(attachment_filepath, attachment_buffer, file_size);
        
	}
	
	
	private int read(byte[] attachment_buffer, BASE64DecoderStream decoder_stream) throws IOException {
		BufferedInputStream buffered_input_stream;
		int file_size;
		
		buffered_input_stream = new BufferedInputStream(decoder_stream);
		file_size = buffered_input_stream.read(attachment_buffer);
        buffered_input_stream.close();
        
        return file_size;
	}
	
	
	private void save(String attachment_filepath, byte[] attachment_buffer, int file_size) throws IOException {
		FileOutputStream file_output_stream;
		BufferedOutputStream buffered_output_stream;		
		file_output_stream = new FileOutputStream(attachment_filepath);
        buffered_output_stream = new BufferedOutputStream(file_output_stream);
        //buffered_output_stream.write(attachment_buffer, file_size);
        buffered_output_stream.write(attachment_buffer, 0, file_size);
        buffered_output_stream.close();
	}
	
	
	private Session getMailSession(){
		Properties props;
		props = System.getProperties();
		props.put("mail.host", "smtp.dummydomain.com");
		props.put("mail.transport.protocol", "smtp");
		return Session.getDefaultInstance(props, null);
	}
	
	
	private String get_data_by_regex(String source, String str_pattern){
		Pattern pattern; Matcher matcher;
		pattern =Pattern.compile(str_pattern, Pattern.MULTILINE);
		matcher = pattern.matcher(source);
		if(matcher.find()){
			return matcher.group(1);
		}else{
			return null;
		}
	}
}

