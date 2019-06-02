package actions.chooser_dialogs;
import java.io.File;
import javax.swing.filechooser.FileNameExtensionFilter;




// Save와 Open기능을 구현할 것
public class SheetFileChooser extends SystemUI_FileChooser
{	

	public SheetFileChooser()
	{
		setFileFilter(new FileNameExtensionFilter("시트 파일(.csv)", "csv"));
	}
	
	
	public File showSaveDialog() {
		int dialog_result;		
		dialog_result = super.showSaveDialog(null);	
		return resultToFile(dialog_result);
	}

	public File showOpenDialog() {		
		int dialog_result;		
		dialog_result = super.showOpenDialog(null);	
		return resultToFile(dialog_result);
	}
	
	
	private File resultToFile(int dialog_result) {
		File file;		
		if (dialog_result==APPROVE_OPTION) {
			file = getSelectedFile();
		} else {
			file = null;
		}
		return file;
	}
}