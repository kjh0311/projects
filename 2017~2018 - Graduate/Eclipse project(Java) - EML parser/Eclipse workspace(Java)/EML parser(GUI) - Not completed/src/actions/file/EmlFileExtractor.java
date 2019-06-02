package actions.file;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;
import java.util.Properties;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.mail.BodyPart;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.internet.MimeUtility;

public class EmlFileExtractor
{	
	
	private static final String 
	//ROW_FORMAT = "%s,%s,%s,%s,%s,%s\n",
	DATE_AND_TIME_PATTERN = "Time of Session \\(UTC\\): (.+)",
	ATTACHMENT_FILE_SIZE_PATTERN = "size=(\\d+);";
	
	
	private Session mail_session;	
	public EmlFileExtractor()
	{
		mail_session = getMailSession();
	}	
	

	// csv 파일의 한 줄의 형태로 리턴
	public String extractEmlFile(File file)
	{		
		try
		{			
			return eml_content_to_string(file);
		}
		catch (Exception e)
		{
			e.printStackTrace();
			System.exit(0);
			return null;
		}		
	}

	
	private String eml_content_to_string(File file) throws IOException, MessagingException, ParseException
	{
		FileInputStream source;
		MimeMessage message;
		Object content;
		String file_name;
		
		
		source = new FileInputStream(file);
		message = new MimeMessage(mail_session, source);
		content = message.getContent();
		source.close();		
		file_name = file.getName();
		
		
		if(content instanceof MimeMultipart){
			// 첨부파일이 있는 경우
			MimeMultipart multipart = (MimeMultipart)content;			
			return eml_content_to_string_in_multipart(multipart, file_name);					
		}
		else
		{
			StringBuilder bulider;
			String text, date_and_time;
			
			
			bulider = new StringBuilder(file_name);
			text = (String)content;
			date_and_time = get_data_by_regex(text, DATE_AND_TIME_PATTERN);
			date_and_time = convert_date_and_time(date_and_time);
			bulider.append(",");
			bulider.append(date_and_time);
			// 첨부파일이 없는 메일은 이렇게 기록만 함.
			return bulider.toString();					
		}
	}

	
	private String eml_content_to_string_in_multipart(MimeMultipart multipart, String file_name) throws MessagingException, IOException, ParseException
	{
		
		StringBuilder bulider;
		
		bulider = new StringBuilder(file_name);
		
		for (int i=0; i<multipart.getCount(); i++)
		{
			BodyPart bodypart;
			String content_type;			
			bodypart = multipart.getBodyPart(i);
			content_type = bodypart.getContentType().split("/")[0];			
			if (content_type.equals("text"))
			{
				String text, date_and_time;
				text = (String) bodypart.getContent();
				date_and_time = get_data_by_regex(text, DATE_AND_TIME_PATTERN);
				if (date_and_time==null) {
					return "";
				} else {
					date_and_time = convert_date_and_time(date_and_time);
					bulider.append(",");
					bulider.append(date_and_time);
				}
				
			}
			else if(content_type.equals("application"))
			{				
				String attachment_name;				
				attachment_name = MimeUtility.decodeText(bodypart.getFileName());
				bulider.append(",");
				bulider.append(attachment_name);
			}
		}		
		return bulider.toString();
	}


	private String convert_date_and_time(String date_and_time) throws ParseException
	{
		Date date;
		SimpleDateFormat original_format, new_format;
		String original_format_str, new_format_str;
		
		
		original_format_str = "EEE MMM dd HH:mm:ss yyyy";
		new_format_str = "yyyy,MM,dd,HH:mm:ss";
		
		original_format = new SimpleDateFormat(original_format_str, Locale.ENGLISH);
		new_format = new SimpleDateFormat(new_format_str, Locale.ENGLISH);
		
		//System.out.println(date_and_time);
		//System.out.println(original_format);
		date = original_format.parse(date_and_time);
		return new_format.format(date);
	}


	private Session getMailSession()
	{
		Properties props;
		props = System.getProperties();
		props.put("mail.host", "smtp.dummydomain.com");
		props.put("mail.transport.protocol", "smtp");
		return Session.getDefaultInstance(props, null);
	}
	
	
	private String get_data_by_regex(String source, String str_pattern)
	{
		Pattern pattern; Matcher matcher;
		pattern =Pattern.compile(str_pattern, Pattern.MULTILINE);
		matcher = pattern.matcher(source);
		if(matcher.find())
		{
			return matcher.group(1);
		}
		else
		{
			return null;
		}
	}
}
