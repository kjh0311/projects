package eml_parser_no_ui;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.mail.MessagingException;
import javax.mail.Session;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

import com.sun.mail.util.BASE64DecoderStream;

public class TimeAndSbdGetter
{
	private static final String
	DATE_AND_TIME_PATTERN = "Time of Session \\(UTC\\): (.+)";
	
	private final String string_output_csv_dir;
	private final Session mail_session;
	
	
	private String time;
	private int attachment_size;
	private BufferedInputStream sbd_input_stream;
	
	

	public TimeAndSbdGetter(String string_output_csv_dir, Session mail_session)
	{
		this.string_output_csv_dir = string_output_csv_dir;
		this.mail_session = mail_session;
	}

	public void parse(File input_eml_file)
	{
		Object content;
		
		content = getContent(input_eml_file);
		if(content instanceof MimeMultipart){
			// 첨부파일이 있는 경우
			//System.out.println("첨부파일이 있는 경우");
			MimeMultipart multipart = (MimeMultipart)content;			
			try
			{
				parse_time_and_attachment_in_multipart(multipart);
			} catch (MessagingException e)
			{				
				e.printStackTrace();
			} catch (IOException e)
			{				
				e.printStackTrace();
			}					
		}else{
			// 첨부파일이 없는 메일은 이렇게 기록만 함.
			String text;
			text = (String)content;
			time = get_data_by_regex(text, DATE_AND_TIME_PATTERN);
			sbd_input_stream = null;
		}
	}

	private void parse_time_and_attachment_in_multipart(MimeMultipart multipart) throws MessagingException, IOException
	{
		for (int i=0; i<multipart.getCount(); i++){
			MimeBodyPart bodypart;
			String content_type;			
			bodypart = (MimeBodyPart) multipart.getBodyPart(i);
			content_type = bodypart.getContentType().split("/")[0];			
			if (content_type.equals("text")){
				String text;				
				text = (String) bodypart.getContent();
				time = get_data_by_regex(text, DATE_AND_TIME_PATTERN);
				//System.out.println("time: "+time);
			}else if(content_type.equals("application")){
				//System.out.println("save_attachment");
				parse_attachment(bodypart);
			}
		}
	}

	private void parse_attachment(MimeBodyPart bodypart) throws MessagingException, IOException
	{
		int attachment_size_limit;
		byte[] attachment_buffer;
		BASE64DecoderStream decoder_stream;
		ByteArrayInputStream byte_array_input_stream;
		DataInputStream data_input_stream;
		
		
		attachment_size_limit = bodypart.getSize();
		attachment_buffer = new byte[attachment_size_limit];
		decoder_stream = (BASE64DecoderStream) bodypart.getContent();
		attachment_size = read(attachment_buffer, decoder_stream);
		byte_array_input_stream = new ByteArrayInputStream(attachment_buffer);		
		sbd_input_stream = new BufferedInputStream(byte_array_input_stream);		
		data_input_stream = new DataInputStream(sbd_input_stream);
		
		//System.out.println("value: "+data_input_stream.readShort());
		
		/*
		FileOutputStream file_output_stream;
		BufferedOutputStream buffered_output_stream;		
		file_output_stream = new FileOutputStream("1.sbd");
        buffered_output_stream = new BufferedOutputStream(file_output_stream);
        buffered_output_stream.write(attachment_buffer, 0, attachment_size);
        buffered_output_stream.close();
        */
	}
	
	private int read(byte[] attachment_buffer, BASE64DecoderStream decoder_stream) throws IOException {
		BufferedInputStream buffered_input_stream;
		int file_size;
		
		buffered_input_stream = new BufferedInputStream(decoder_stream);
		file_size = buffered_input_stream.read(attachment_buffer);
        buffered_input_stream.close();
        
        return file_size;
	}

	private Object getContent(File input_eml_file)
	{
		FileInputStream source;
		MimeMessage message;
		
		try
		{
			source = new FileInputStream(input_eml_file);			
			message = new MimeMessage(mail_session, source);
			return message.getContent();
		} catch (MessagingException | IOException e)
		{
			e.printStackTrace();
			return null;
		}
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

	public String getTime()
	{
		return time;
	}
	
	public int getAttachmentSize(){
		return attachment_size;
	}

	public BufferedInputStream getSbdInputStream()
	{
		return sbd_input_stream;
	}

}
