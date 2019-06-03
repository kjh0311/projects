package kjh.running_machine_exercise_infomation_shower.tab1;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import kjh.running_machine_exercise_infomation_shower.MainActivity;

/**
 * Created by com on 2016-02-17.
 */


public class Tab1DBHelper extends SQLiteOpenHelper {
	// 나는 static final에 한해서만 대문자로 하겠다.
	// static이 붙은 것은 공통속성이다.
	private static final String
			DATABASE_NAME = "database",
			TABLE_NAME = "settingTBL";

	// 관리하기 쉽게 할려고 이렇게 만듬
	class ColumnNames {
		static final String
		CURRENT_GRAD = "CURRENT_GRAD",
		CURRENT_SPEED = "CURRENT_SPEED",
		START_GRAD = "START_GRAD",
		START_SPEED = "START_SPEED";
	}

	// static이 안 붙은 것은, 이 클래스 인스턴스의 고유속성이다.
	private final String my_column;

	MainActivity activity;
	// 각 인스턴스 마다 실행
	public Tab1DBHelper(MainActivity context, CurrentOrStart current_or_start, GradOrSpeed grad_or_speed) {
		// 여기서 데이터 베이스 이름 지정
		super(context, DATABASE_NAME, null, 1);
		this.activity = context;

		my_column = get_my_column(current_or_start, grad_or_speed);
		initialize_database();
	}


	private void initialize_database() {
		SQLiteDatabase db;
		// 객체 생성이 다 끝나기 전까지는 아래의 것을 부르면 안 될 듯
		//db = getWritableDatabase();

		Context context;
		db = activity.openOrCreateDatabase(DATABASE_NAME, activity.MODE_PRIVATE, null);
		create_table_if_not_exists(db);
		if ( table_is_empty(db) ) {
			create_row(db);
		}
		db.close();
	}


	private void create_table_if_not_exists(SQLiteDatabase db) {
		// 띄어쓰기 조심해야함
		String query;
		query =	"CREATE TABLE "+
				"IF NOT EXISTS " +
				TABLE_NAME + "(" +
				ColumnNames.CURRENT_GRAD	+ " value FLOAT(2,1) ,"+
				ColumnNames.CURRENT_SPEED	+ " value FLOAT(2,1) ,"+
				ColumnNames.START_GRAD		+ " value FLOAT(2,1) ,"+
				ColumnNames.START_SPEED		+ " value FLOAT(2,1) "+
				");";
		db.execSQL(query);
	}

	private boolean table_is_empty(SQLiteDatabase db) {
		Cursor cursor;
		int count;
		String query = "SELECT * FROM "+ TABLE_NAME +";";
		cursor = db.rawQuery(query, null);
		count = cursor.getCount();
		if (count == 0) {
			return true;
		}
		else {
			return false;
		}
	}

	private void create_row(SQLiteDatabase db) {
		String query;
		query = "INSERT INTO " + TABLE_NAME
				+ " VALUES (0.0, 0.0, 0.0, 0.0);"
		;
		db.execSQL(query);
	}


	public void write_value(double value) {

		String query;
		SQLiteDatabase db;
		// 띄어쓰기 조심할 것
		query = "UPDATE "+ TABLE_NAME
				+ " SET " + my_column
				+ "=" + value + ";";
		db = getWritableDatabase();
		db.execSQL(query);
		db.close();
	}


	public double read_value() {
		SQLiteDatabase db;
		Cursor cursor;
		String query;
		double value;

		db = getReadableDatabase();
		query = "SELECT "+ my_column +" FROM " + TABLE_NAME + ";";
		cursor = db.rawQuery(query, null);
		// cursor.moveToNext(); 를 안 붙혀주면 오류남. 이상한 체계임.
		cursor.moveToNext();
		value = cursor.getDouble(0);
		db.close();
		return value;
	}

	private String get_my_column(CurrentOrStart current_or_start, GradOrSpeed grad_or_speed) {
		if ( current_or_start == CurrentOrStart.CURRENT ) {
			if (grad_or_speed == GradOrSpeed.GRAD )
				return ColumnNames.CURRENT_GRAD;
			else
				return ColumnNames.CURRENT_SPEED;
		} else {
			if (grad_or_speed == GradOrSpeed.GRAD )
				return ColumnNames.START_GRAD;
			else
				return ColumnNames.START_SPEED;
		}
	}


	// 데이터베이스가 생성될 때만 실행
	// 즉, 데이터베이스가 비어있다면 오류임.
	@Override
	public void onCreate(SQLiteDatabase db) {

	}

	// 아래의 것은 초기화임
	@Override
	public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
		String query = "DROP TABLE IF EXISTS "+ TABLE_NAME;
		db.execSQL(query);
		onCreate(db);
	}
}
