package actions.chooser_dialogs;

import java.awt.Component;

import javax.swing.JFileChooser;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;

abstract class SystemUI_FileChooser extends JFileChooser
{		
	@Override
	public int showDialog(Component parent, String approveButtonText) {
		//System.out.println("showDialog");
		
		int result;
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
			updateUI();
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
		
		
		result = super.showDialog(parent, approveButtonText);
		
		try {
			UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
			updateUI();
		} catch (ClassNotFoundException | InstantiationException | IllegalAccessException
				| UnsupportedLookAndFeelException e) {
			e.printStackTrace();
		}
		
		return result;
	}
}
