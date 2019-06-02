package actions.chooser_dialogs;

import java.io.File;
import java.io.FilenameFilter;

import javax.swing.filechooser.FileNameExtensionFilter;

public class EmlFilesDirChooser  extends SystemUI_FileChooser
{
	
	public EmlFilesDirChooser()
	{
		setFileSelectionMode(DIRECTORIES_ONLY);
		setFileFilter(new FileNameExtensionFilter("eml 파일을 저장한 폴더", "."));
	}
	
	
	public File showOpenDialog() {
		
		
		File dir;
		int dialog_result;		
		
		
		dialog_result = super.showOpenDialog(null);	
		if (dialog_result==APPROVE_OPTION) {
			dir = getSelectedFile();
		} else {
			dir = null;
		}	
		return dir;
	}
}
