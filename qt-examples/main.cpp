// various Qt snippets to experiment with basic things


#include <QString>
#include <QTextStream>
#include <QDir>

int main()
{
	// QString examples
	QTextStream stdout_(stdout);
	QString test_qstring("this is a test");

	stdout_ << test_qstring << "\n";

	QString arg1 = QString("test #%1").arg(23);

	stdout_ << arg1 << "\n";

	QString * arg2 = new QString("test arg2");

	stdout_ << *arg2 << "\n";

	QString * arg3;
       
	arg3 = new QString(QString("arg%1, test %2").arg(3).arg(10));

	stdout_ << *arg3 << "\n";

	// QDir examples
	QDir etc("/etc");

	bool etc_exists = etc.exists();

	stdout_ << "the /etc exists returns " << etc_exists << "\n";


	// QTextStream examples
	{
		QFile file("/etc/hosts");
		if (! file.open(QIODevice::ReadOnly)) {
			stdout_ << "Error opening " << file.fileName() << "\n";
			return -1;
		}

		QTextStream stream1(&file);

		QString first_line, second_line;

		first_line = stream1.readLine();
		second_line = stream1.readLine();

		stdout_ << "First line = " << first_line << "\n";
		stdout_ << "Second line = " << second_line << "\n";

		QTextStream stream3(&first_line);

		int number;
		stream3 >> number;

		stdout_ << "parsed number = " << number << "\n";

		QString first_word, second_word;

		stream1 >> first_word >> second_word;

		stdout_ << "First word = " << first_word << "\n";
		stdout_ << "Second word = " << second_word << "\n";

		// Turn a QSTring into a text stream
		QTextStream stream2("this is a test");

		QString word;
		stream2 >> word;

		stdout_ << "First word = " << word << "\n";
	}

	return 0;
}
