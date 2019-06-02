package main;
import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
public class Main {
	public static int cols = 8;
	public static int rows = 8;
	public static boolean record[][];
	
	public static void main(String args[])
	{		
		new Main();
		initRecord();
		/*
		// 초기화 이상 무
		for (int i = 0; i<Main.rows; i++){
			for (int j = 0; j<Main.cols; j++){
				System.out.print(record[i][j]);
			}
			System.out.println();
		}
		*/
	}
	Main()
	{
		new MainWindow();
	}
	
	public static void initRecord(){
		record = new boolean[cols][rows];	
	}
}


class MainWindow extends JFrame{
	public static JTextField explainTextField;
	public static JTextField varNameField;
	public static JTextField prefixField;
	MainWindow()
	{
		setTitle("김진희의 ATmega128 GLCD 문자 생성기");
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setBounds(600,550,460,400);		
		createButton();
	}
	
	Container c;
	JPanel gridPanel, controlPanel;
	void createButton()
	{
		
		c = getContentPane();
		c.setLayout(new BorderLayout());
		
		
		createGridPanel();		
		
		
		controlPanel = new JPanel();		
		c.add(controlPanel, BorderLayout.EAST);		
		
		
		controlPanel.setLayout(new GridLayout(Main.rows,1));
		explainTextField = new JTextField();
		varNameField = new JTextField();
		prefixField = new JTextField("font");
		
		controlPanel.add(new StoreButton());
		controlPanel.add(new JLabel("설명"));		
		controlPanel.add(explainTextField);
		controlPanel.add(new JLabel("변수명"));		
		controlPanel.add(varNameField);
		controlPanel.add(new JLabel("관습 접두어"));		
		controlPanel.add(prefixField);
		controlPanel.add(new InitButton(this));
		
		validate();
	}
	private void createGridPanel() {
		gridPanel = new JPanel();
		c.add(gridPanel, BorderLayout.CENTER);		
		gridPanel.setLayout(new GridLayout(Main.rows,Main.cols));		
		for (int i = 0; i<Main.rows; i++)
		for (int j = 0; j<Main.cols; j++)
			gridPanel.add(new ToggleButton(i,j));		
	}
	public void initGridButtons() {		
		c.remove(gridPanel);
		createGridPanel();
		validate();
	}	
}

class ToggleButton extends JButton implements ActionListener{	
	boolean checked = false;
	int row, col;
	ToggleButton(int i, int j){
		row = i;
		col = j;
		addActionListener(this);
	}

	@Override
	public void actionPerformed(ActionEvent arg0)
	{
		if ( checked )
		{
			setText("");
			checked = false;
			Main.record[row][col]=false;
		}
		else
		{
			setText("■");
			checked = true;
			Main.record[row][col]=true;
			/*
			for (int i = 0; i<Main.rows; i++){
				for (int j = 0; j<Main.cols; j++){
					System.out.print(Main.record[i][j]+"\t");
				}
				System.out.println();
			}
			*/
		}
	}
}


class StoreButton extends JButton implements ActionListener{
	StoreButton(){
		setText("저장");
		addActionListener(this);
	}
	
	@Override
	public void actionPerformed(ActionEvent arg0)
	{	
		//System.out.println("저장버튼 눌림");
		// 행위를 객체로 간주
		Compile c = new Compile();
		c.Store();
	}
	
}


class InitButton extends JButton implements ActionListener{
	MainWindow mainWindow;
	InitButton(MainWindow window){
		setText("초기화");
		addActionListener(this);
		mainWindow = window;
	}

	@Override
	public void actionPerformed(ActionEvent arg0) {
		Main.initRecord();
		mainWindow.initGridButtons();
	}	
}


class Compile{
	
	public int result[] = new int[Main.cols];
	Compile(){
		for(int i=0;i<Main.rows;i++){
			for(int j=0;j<Main.cols;j++){
				if (Main.record[i][j]){
					result[j] |= 1<<i;
				}
			}
		}
	}
	
	void Store()
	{		
		String s = "{";
		String explainText;
		String varName;
		String prefix;
		
		
		varName = MainWindow.varNameField.getText();
		if (!varName.equals("")){			
			prefix = MainWindow.prefixField.getText();
			if (!prefix.equals(""))
				varName = prefix +"_"+varName;
			varName = "const char " + varName;
			s = varName + "["+Main.cols+"] = " + s;
		}		
		
		s += getHex(result[0]);
		for (int i=1; i<Main.rows;i++){
			s += ", ";
			s += getHex(result[i]);
		}
		s += "};";
		
		explainText = MainWindow.explainTextField.getText();
		if (!explainText.equals("")){
			s += "\t// "+explainText;
		}
		
		s += "\r\n"; // 경험의 결과. 이게바로 융합이다.
		
		System.out.println(s);
		
		StoreToFile(s);		
	}
	
	
	void StoreToFile(String s)
	{
		File f = new File("생성된 코드.txt");		
		try
		{
			FileWriter fw;
			fw = new FileWriter(f, true);
			BufferedWriter bw = new BufferedWriter(fw);
			bw.write(s);
			bw.close();
		}
		catch (IOException e)
		{
			e.printStackTrace();
		}		
	}
	
	
	private String getHex(int iv){
		String hex = "";		
		hex = Integer.toHexString(iv).toUpperCase();
		if (hex.length()==1)
			hex = "0"+hex;
		hex = "0X"+hex;
		return hex;
	}
}
