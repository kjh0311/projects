package kjh.running_machine_exercise_infomation_shower.database;

import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

import kjh.running_machine_exercise_infomation_shower.MainActivity;
import kjh.running_machine_exercise_infomation_shower.tab2.action_setter.*;

/**
 * Created by com on 2016-02-19.
 */
public class DB_Helper extends SQLiteOpenHelper
{
	private static final String
			DATABASE_NAME = "database",
			TABLE_NAME = "exercise_info";
	// 관리하기 쉽게 할려고 이렇게 만듬
	class ColumnNames
	{
		static final String
			DATE = "DATE",
			START_TIME = "START_TIME",
			END_TIME = "END_TIME",
			KCAL = "KCAL",
			KM = "KM",
			GRAD = "GRAD",
			SPEED = "SPEED";
	}
	MainActivity activity;
	SQLiteDatabase db;
	public DB_Helper(MainActivity context)
	{
		super(context, DATABASE_NAME, null, 1);
		activity = context;
		create_table_if_not_exists();
	}

	private void create_table_if_not_exists()
	{
		String query;
		query = "CREATE TABLE "+
				"IF NOT EXISTS " +
				TABLE_NAME + "(" +
				ColumnNames.DATE			+ " value DATE ,"+
				ColumnNames.START_TIME		+ " value TIME ,"+
				ColumnNames.END_TIME		+ " value TIME ,"+
				ColumnNames.KCAL			+ " value INT(4) ,"+
				ColumnNames.KM				+ " value FLOAT(3,1) ,"+
				ColumnNames.GRAD			+ " value FLOAT(2,1) ,"+
				ColumnNames.SPEED			+ " value FLOAT(2,1) "+
				");";
		db = getWritableDatabase();
		db.execSQL(query);
		db.close();
	}


	public void insert(StringBuilder insert_parameter)
	{
		String query;
		query = "INSERT INTO " + TABLE_NAME
				+ " values ("
				+ insert_parameter
				+ ");";
		db = getWritableDatabase();
		db.execSQL(query);
		db.close();
	}

	public DB_Values getValuesBySpinnerValue(int spinner_value)
	{
		Cursor cursor;
		cursor = getCursorBySpinnerValue(spinner_value);
		return getValuesByCursor(cursor);
	}

	public DB_Values getValuesByDate(int year, int month, int day)
	{
		Cursor cursor;
		cursor = getCursorByDate(year, month, day);
		return getValuesByCursor(cursor);
	}


	private Cursor getCursorBySpinnerValue(int spinner_value)
	{
		String sql;
		sql = getSqlBySpinnerValue(spinner_value);
		return getCorsorBySQL(sql);
	}

	private Cursor getCursorByDate(int year, int month, int day)
	{
		String sql;
		sql = getSqlByDate(year, month, day);
		return getCorsorBySQL(sql);
	}


	private String getSqlBySpinnerValue(int spinner_value)
	{
		String sql, sql_select, sql_range;

		sql_select = getSqlSelect();
		sql_range = getSqlRange(spinner_value);
		sql = sql_select + sql_range + ";";
		return sql;
	}

	public String getSqlByDate(int year, int month, int day)
	{
		String sql, sql_select, sql_date;

		sql_select = getSqlSelect();
		sql_date = getSqlDate(year, month, day);
		sql = sql_select + sql_date + ";";
		return sql;
	}


	private String getSqlSelect()
	{
		String sql_select, sql_time_distance;

		sql_time_distance = getSqlTimeDistance();
		sql_select = "SELECT "
				+ ColumnNames.DATE + ","
				+ ColumnNames.START_TIME +", "
				+ ColumnNames.END_TIME +", "
				+ sql_time_distance + ","
				+ ColumnNames.KCAL +", "
				+ ColumnNames.KM +", "
				+ ColumnNames.GRAD +", "
				+ ColumnNames.SPEED
				+ " FROM " + TABLE_NAME;
		return sql_select;
	}


	private String getSqlTimeDistance()
	{
		String sql_time_distance;
		sql_time_distance =
				"strftime( '%H:%M', " +
						"strftime('%s', " + ColumnNames.END_TIME + ")" +
						"- strftime('%s', " + ColumnNames.START_TIME + ")" +
						", 'unixepoch')";
		return sql_time_distance;
	}



	private String getSqlRange(int spinner_value)
	{
		String sql_range, sql_days, sql_time_distance;
		sql_days = spinner_value_to_sql(spinner_value);
		sql_range = sql_days
				+ " ORDER BY "
				+ ColumnNames.DATE + " || "
				+ ColumnNames.START_TIME
				+ " DESC";
		return sql_range;
	}

	private String getSqlDate(int year, int month, int day)
	{
		String sql_date, str_year, str_month, str_day;

		str_year = Integer.toString(year);
		str_month = int_to_2digit_string(month);
		str_day = int_to_2digit_string(day);
		sql_date = " WHERE " + ColumnNames.DATE + " = "
				+ "'" + str_year + "-" + str_month + "-" + str_day + "'";
		return sql_date;
	}


	private String spinner_value_to_sql(int spinner_value)
	{
		String sql;
		sql = " WHERE " + ColumnNames.DATE
				+ " > date('now', 'localtime', '-";
		switch (spinner_value)
		{
			case SpinnerViewActionSetter.ONE_DAY:
				return sql+"1 day')";
			case SpinnerViewActionSetter.THREE_DAYS:
				return sql+"3 day')";
			case SpinnerViewActionSetter.FIVE_DAYS:
				return sql+"5 day')";
			case SpinnerViewActionSetter.ONE_WEEK:
				return sql+"7 day')";
			case SpinnerViewActionSetter.TWO_WEEKS:
				return sql+"14 day')";
			case SpinnerViewActionSetter.ONE_MONTH:
				return sql+"1 month')";
			case SpinnerViewActionSetter.ONE_YEAR:
				return sql+"1 year')";
			default:
				return "";
		}
	}

	private String int_to_2digit_string(int day)
	{
		String two_digit_str;
		two_digit_str = Integer.toString(day);
		while ( two_digit_str.length() < 2)
		{
			two_digit_str = "0" + two_digit_str;
		}
		return two_digit_str;
	}

	private DB_Values getValuesByCursor(Cursor cursor)
	{
		DB_Values values;
		values = null;
				/*
		가장 오래된 것 부터 values에 넣어서,
		가장 마지막에는 values가 가장 최근의 것을
		가리킨다.
		 */
		cursor.moveToLast();
		if (cursor.getCount() > 0) {
			do {
				values = new DB_Values(cursor, values);
			}
			while (cursor.moveToPrevious());
		}
		cursor.close();
		db.close();
		return values;
	}

	private Cursor getCorsorBySQL(String sql)
	{
		Cursor cursor;
		db = getReadableDatabase();
		cursor = db.rawQuery(sql, null);
		return cursor;
	}

	public DB_DailyValues getDailyValues(String date)
	{
		Cursor cursor;
		DB_DailyValues values;

		cursor = getDailyCursor(date);
		cursor.moveToNext();

		values = new DB_DailyValues(cursor, date);
		cursor.close();
		db.close();
		return values;
	}


	private Cursor getDailyCursor(String date)
	{
		Cursor cursor;
		String sql;

		sql = getDailySql(date);
		db = getReadableDatabase();
		cursor = db.rawQuery(sql, null);
		return cursor;
	}

	public String getDailySql(String date)
	{
		String sql, sql_time_distance;
		sql_time_distance =
				"strftime( '%H:%M', SUM(strftime('%s'," + ColumnNames.END_TIME + ")"
						+ "- strftime('%s'," + ColumnNames.START_TIME + "))"
						+ ",  'unixepoch' )";
		sql = "SELECT "
				+ sql_time_distance
				+ ", SUM(" + ColumnNames.KCAL
				+ "), SUM(" + ColumnNames.KM
				+ ") FROM " + TABLE_NAME
				+ " WHERE " + ColumnNames.DATE + "= '" + date + "'"
				+ ";";
		return sql;
	}

	@Override
	public void onCreate(SQLiteDatabase sqLiteDatabase)
	{

	}

	@Override
	public void onUpgrade(SQLiteDatabase sqLiteDatabase, int i, int i1)
	{

	}
}
