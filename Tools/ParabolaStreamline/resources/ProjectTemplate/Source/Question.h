#ifndef Question_h__
#define Question_h__

#include <ParabolaCore/Strings.h>
using namespace pE;

#include <vector>

class QuestionOption{
public:
	/// Text of the option
	String m_text;
	/// Whether this is the right option or not 
	bool m_right;
};

class Question{
public:
	/// The display text of the question
	String m_questionText;

	/// The answers of this question
	std::vector<QuestionOption> m_options;
};

#endif // Question_h__
