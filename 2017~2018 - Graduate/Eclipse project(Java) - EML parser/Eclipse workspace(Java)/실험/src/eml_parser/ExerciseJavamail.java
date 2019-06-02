package eml_parser;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import javax.mail.BodyPart;
import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.internet.MimeUtility;

import com.sun.mail.util.BASE64DecoderStream;


import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class ExerciseJavamail
{
	public static void main(String args[]) {
		new ExerciseJavamail();
	}
	
	
	private ExerciseJavamail()
	{
		String file_name = "201701161332475930.eml";
		File file = new File(file_name);
		
		try {		
			FileInputStream source = new FileInputStream(file);
			
			Properties props = System.getProperties();
			props.put("mail.host", "smtp.dummydomain.com");
			props.put("mail.transport.protocol", "smtp");
			Session mailSession = Session.getDefaultInstance(props, null);		
			
			MimeMessage message = new MimeMessage(mailSession, source);
			MimeMultipart multipart = (MimeMultipart)message.getContent();			
			
			parseMultipart(multipart);			
		} catch (IOException | MessagingException e) {
			e.printStackTrace();
		}
	}
	
	
	private void parseMultipart(MimeMultipart mimeMultipart) throws MessagingException, IOException
	{
		String text = null, filename = null, date_and_time;
		int file_size = 0;
		//List<String> attachments = new ArrayList<String>(1);
		
		
		for (int i = 0; i < mimeMultipart.getCount(); i++)
		{
			BodyPart part = mimeMultipart.getBodyPart(i);
			if (part.getContent() instanceof MimeMultipart)
			{
				parseMultipart((MimeMultipart) part.getContent());
			}
			
			
			Object obj = part.getContent();
			
			
			if (obj instanceof String)
			{
				//String date_and_time;
				String str_file_size, str_pattern;
				Pattern pattern; Matcher matcher;
				
				text = (String)obj;
				
				//text = "Time of Session (UTC): 1234";
				//System.out.println(text);
				
				str_pattern = "Time of Session \\(UTC\\): (.+)";
				pattern =Pattern.compile(str_pattern, Pattern.MULTILINE);
				matcher = pattern.matcher(text);
				
				//date_and_time = matcher.group(1);
				
				
				if ( matcher.find() ) {				
					date_and_time = matcher.group(1);
				} else {
					//System.out.println("날짜 시간 못 찾음");
					date_and_time = "못 찾음";
				}
				
				System.out.println("date_and_time");
				System.out.println(date_and_time);
				
				
				str_pattern = "Message Size \\(bytes\\): (\\d+)";
				pattern =Pattern.compile(str_pattern, Pattern.MULTILINE);
				matcher = pattern.matcher(text);
				
				
				if ( matcher.find() ) {
					str_file_size = matcher.group(1);
					file_size = Integer.parseInt(str_file_size);
				} else {
					//System.out.println("날짜 시간 못 찾음");
					str_file_size = "못 찾음";
				}
				//str_file_size = matcher.group(1);
				
				System.out.println("str_file_size");
				System.out.println(str_file_size);
				//System.exit(0);
				
			}	//첨부파일이 있는 경우 파일을 저장
			else if (obj instanceof BASE64DecoderStream)
			{
            	BASE64DecoderStream newObj = (BASE64DecoderStream) obj;
                filename = MimeUtility.decodeText(part.getFileName());
                
                //file_size = part.getSize();                
                //System.out.println("file_size");
                //System.out.println(file_size);
                
                
                File attacheFile = new File(filename);

                FileOutputStream fos = new FileOutputStream(attacheFile);
                byte[] buffer = new byte[file_size];

                while (0 < newObj.read(buffer)) {
                    fos.write(buffer);
                }
                newObj.close();
                fos.close();
            }
			
			
			System.out.println("part#"+i);
			if (text != null) {
				System.out.println("text");
				System.out.println(text);
				text = null;
			} else if (filename != null) {
				System.out.println("attachment filename");
				System.out.println(filename);
				filename = null;
			}
		}
	}
}
