package eml_parser_no_ui;

import java.io.DataInputStream;
import java.io.FileWriter;
import java.io.IOException;

public class OneSbdPartParser
{
	//private final String string_output_csv_dir;
	private final FileWriter file_writers[];
	private final String name;
	private final int number_of_nodes;
	private final int columns;
	private final double multiplier;
	
	enum Type {
		SHORT, FLOAT;
	}
	private final Type type;
	

	public OneSbdPartParser(final String name, final Type type, final int number_of_nodes, final int columns, 
			final double multiplier, final String string_output_csv_dir)
	{
		this.name = name;
		this.type = type;
		this.number_of_nodes = number_of_nodes;
		this.columns = columns;
		this.multiplier = multiplier;
		//this.string_output_csv_dir = string_output_csv_dir;
		
		
		file_writers = new FileWriter[number_of_nodes];
		for(int i=0; i<number_of_nodes; i++){
			String file_name = string_output_csv_dir + "/" + name + "_" + (i+1) + ".csv";
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

	public void parse_sbd(String time, DataInputStream sbd_data_input_stream) throws IOException
	{		
		switch (type) {
		case SHORT:
			parse_sbd_short(time, sbd_data_input_stream);
			break;
		case FLOAT:
			parse_sbd_float(time, sbd_data_input_stream);
			break;	
		}
	}
	
	
	private void parse_sbd_short(String time, DataInputStream sbd_data_input_stream) throws IOException
	{
		/*
		System.out.println(name);
		if (name.startsWith("CO2")) {
			System.out.println(name);
			System.out.println(number_of_nodes);
			System.exit(0);
		}
		*/
		for (int i=0; i<number_of_nodes; i++) {
			short value;
			FileWriter file_writer;				
			
			file_writer = file_writers[i];
			file_writer.write(time+",");
			for (int j=0; j<columns-1; j++) {
				value = sbd_data_input_stream.readShort();
				file_writer.write(value*multiplier+",");
			}
			value = sbd_data_input_stream.readShort();
			file_writer.write(value*multiplier+"\n");
		}
	}
	
	
	private void parse_sbd_float(String time, DataInputStream sbd_data_input_stream) throws IOException
	{		
		for (int i=0; i<number_of_nodes; i++) {
			float value;
			FileWriter file_writer;				
			
			file_writer = file_writers[i];
			file_writer.write(time+",");
			for (int j=0; j<columns-1; j++) {
				value = readAndSwapFloat(sbd_data_input_stream);
				file_writer.write(value*multiplier+",");
			}
			value = readAndSwapFloat(sbd_data_input_stream);
			file_writer.write(value*multiplier+"\n");
		}
	}
	
	private float readAndSwapFloat(DataInputStream sbd_data_input_stream) throws IOException {
		float value;
		value = sbd_data_input_stream.readFloat();
		value = swap(value);
		return value;
	}
	
	
	private float swap(float x) { 
		return Float.intBitsToFloat(swap(Float.floatToRawIntBits(x))); 
	}
	
	private int swap(int x) {
		return (int)((swap((short)x) << 16) | swap((short)(x >> 16)) & 0xffff);
	}
	
	private short swap(short x) { 
		return (short)((x << 8) | ((x >> 8) & 0xff)); 
	}
	

	public void write_time(String time) throws IOException
	{
		for (int i=0; i<number_of_nodes; i++) {
			FileWriter file_writer;				
			
			file_writer = file_writers[i];
			file_writer.write(time+"\n");
		}
	}

}
