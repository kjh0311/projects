package program_start;

import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileWriter;
import java.io.IOException;

public class ResultFilesWriter
{
	private static final String
		RESULT_CSV_DIR = "result_csv";	
	private ParameteredWriters rtd, tc, co2;
	
	
	public ResultFilesWriter(){
		File csv_dir;
		csv_dir = new File(RESULT_CSV_DIR);
		if (csv_dir.exists() == false){
			csv_dir.mkdir();
		}
		
		// 파일을 연다.
		rtd = new ParameteredWriters("RTD", 12, 4, 1);
		tc = new ParameteredWriters("TC", 7, 8, 0.25);
		co2 = new ParameteredWriters("CO2", 3, 1, 1);
	}
	
	
	public void close()
	{
		// 파일을 닫는다.
		rtd.close();
		tc.close();
		co2.close();
	}


	public void write(File sbd_file)
	{
		DataInputStream data_input_stream;
		try
		{
			data_input_stream = new DataInputStream(new BufferedInputStream(new FileInputStream(sbd_file)));
			
			rtd.write(data_input_stream);
			tc.write(data_input_stream);
			co2.write(data_input_stream);
			
			data_input_stream.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}	
	}
	
	
	private class ParameteredWriters {
		
		private final FileWriter file_writers[];
		private final int number_of_nodes;
		private final int columns;
		private final double multiplier;
		
		
		ParameteredWriters(final String name, final int number_of_nodes, final int columns, final double multiplier){
			
			this.number_of_nodes = number_of_nodes;
			this.columns = columns;
			this.multiplier = multiplier;
			
			
			file_writers = new FileWriter[number_of_nodes];
			for(int i=0; i<number_of_nodes; i++){
				String file_name = RESULT_CSV_DIR + "/" + name + "_" + (i+1) + ".csv";
				try
				{
					file_writers[i] = new FileWriter(file_name);
				} catch (IOException e)
				{
					e.printStackTrace();
				}
			}
		}


		public void close()
		{
			for (int i=0; i<number_of_nodes; i++) {
				try
				{
					file_writers[i].close();
				} catch (IOException e)
				{
					e.printStackTrace();
				}
			}
		}


		public void write(DataInputStream data_input_stream) throws IOException
		{			
			for (int i=0; i<number_of_nodes; i++) {
				short value;
				FileWriter file_writer;				
				
				file_writer = file_writers[i];
				for (int j=0; j<columns-1; j++) {
					value = data_input_stream.readShort();
					file_writer.write(value*multiplier+"");
					file_writer.write(",");
				}
				value = data_input_stream.readShort();
				file_writer.write(value+"");
				file_writer.write("\n");
			}
		}
	}
	
	

	
	
}
