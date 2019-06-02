package eml_parser_no_ui;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Properties;
import javax.mail.Session;

import eml_parser_no_ui.OneSbdPartParser.Type;

public class OneEmlFileParser
{
	private final String string_output_csv_dir;
	
	private OneSbdPartParser rtd, tc, co2, wc;
	private final Session mail_session;
	
	public OneEmlFileParser(String string_output_csv_dir)
	{
		this.string_output_csv_dir = string_output_csv_dir;
		
		File csv_dir;
		csv_dir = new File(string_output_csv_dir);
		if (csv_dir.exists() == false){
			csv_dir.mkdir();
		}
		
		rtd = new OneSbdPartParser("RTD", Type.SHORT, 12, 4, 1, string_output_csv_dir);
		tc = new OneSbdPartParser("TC", Type.SHORT, 7, 8, 0.25, string_output_csv_dir);
		co2 = new OneSbdPartParser("CO2", Type.SHORT, 1, 8, 5000.0/4095.0, string_output_csv_dir);
		wc = new OneSbdPartParser("WC", Type.FLOAT, 12, 2, 1, string_output_csv_dir);
		
		mail_session = getMailSession();
		
	}

	public void close()
	{
		rtd.close();
		tc.close();
		co2.close();
		wc.close();
	}

	// 날짜와 첨부파일을 얻어내서 파일에 저장
	public void parse(File input_eml_file)
	{
		TimeAndSbdGetter getter;
		String time;
		//int sbd_size;
		DataInputStream sbd_data_input_stream;
		BufferedInputStream sbd_buffered_stream;
		
		getter = new TimeAndSbdGetter(string_output_csv_dir, mail_session);
		getter.parse(input_eml_file);
		
		time = getter.getTime();
		sbd_buffered_stream = getter.getSbdInputStream();
		try {
			if (sbd_buffered_stream == null){
				rtd.write_time(time);
				tc.write_time(time);
				co2.write_time(time);
				wc.write_time(time);
			}
			else
			{				
				sbd_data_input_stream = 
						new DataInputStream(sbd_buffered_stream);		
			
				rtd.parse_sbd(time, sbd_data_input_stream);
				tc.parse_sbd(time, sbd_data_input_stream);
				co2.parse_sbd(time, sbd_data_input_stream);
				wc.parse_sbd(time, sbd_data_input_stream);
				
				sbd_data_input_stream.close();
			}
		} catch (IOException e)
		{
			//System.out.println("number_of_nodes"+number_of_nodes);
			//System.out.println("columns"+columns);
			e.printStackTrace();
		}
	
	}
	
	
	private Session getMailSession(){
		Properties props;
		props = System.getProperties();
		props.put("mail.host", "smtp.dummydomain.com");
		props.put("mail.transport.protocol", "smtp");
		return Session.getDefaultInstance(props, null);
	}

}
