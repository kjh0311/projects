package ui.gui_controller.button;

import java.awt.Rectangle;

import ui.Bounds;
import ui.Strings;

public final class ButtonParameters {		
	public static class MultiLine {
		String strings[]; Rectangle bounds;
	}
	public static class SingleLine {
		String string; Rectangle bounds;
	}

	private static final class LoadEmls extends MultiLine {
		LoadEmls() {
			strings = Strings.LOAD_EMLS;
			bounds = Bounds.Button.LOAD_EMLS;
		}
	}

	private static final class LoadSheet extends MultiLine {
		LoadSheet() {
			strings = Strings.LOAD_SHEET;
			bounds = Bounds.Button.LOAD_SHEET;
		}
	}

	private static final class Save extends SingleLine {
		Save() {
			string = Strings.SAVE;
			bounds = Bounds.Button.SAVE;
		}
	}

	private static final class SaveAs extends SingleLine {
		SaveAs() {
			string = Strings.SAVE_AS;
			bounds = Bounds.Button.SAVE_AS;
		}
	}

	private static final class Clear extends SingleLine {
		Clear() {
			string = Strings.CLEAR;
			bounds = Bounds.Button.CLEAR;
		}
	}
	
	
	private static final class LookUp extends SingleLine {
		LookUp() {
			string = Strings.LOOK_UP;
			bounds = Bounds.SpecifyRange.LOOK_UP;
		}
	}
	

	public static final MultiLine LOAD_EMLS, LOAD_SHEET;
	public static final SingleLine SAVE, SAVE_AS, CLEAR, LOOK_UP;


	static {
		LOAD_EMLS = new LoadEmls();
		LOAD_SHEET = new LoadSheet();
		SAVE = new Save();
		SAVE_AS = new SaveAs();
		CLEAR = new Clear();
		LOOK_UP = new LookUp();
	}
}