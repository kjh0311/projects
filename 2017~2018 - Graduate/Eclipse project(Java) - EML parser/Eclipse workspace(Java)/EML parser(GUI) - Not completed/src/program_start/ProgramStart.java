package program_start;

import java.awt.Font;

import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

public class ProgramStart {	
	public static void main(String[] args) {
		/*
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
		*/
		new ProgramStart();
	}	
	
	private ProgramStart() {		
		GuiController gui_controller;
		Actions actions;
		DataController data_controller;
		
		
		
		gui_controller = new GuiController();
		data_controller = new DataController();
		actions = new Actions(data_controller);
		
		
		// 이게 호출된 이후 시점에 생성되는 것부터 다르게 생성됨
		setUIFont(new javax.swing.plaf.FontUIResource("돋움", Font.PLAIN, 13));
		// 초기의 것을 그림
		gui_controller.showInitAll();
		// 사용자로부터 입력받았을 때 행동을 하게함.
		gui_controller.addActions(actions);
		data_controller.addGuiController(gui_controller);
	}
	
	
	public void setUIFont(javax.swing.plaf.FontUIResource f) {
		java.util.Enumeration keys = UIManager.getDefaults().keys();
		while (keys.hasMoreElements()) {
			Object key = keys.nextElement();
			Object value = UIManager.get(key);
			if (value instanceof javax.swing.plaf.FontUIResource)
				UIManager.put(key, f);
		}
	}
}










