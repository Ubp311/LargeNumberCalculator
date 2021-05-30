#include	<iostream>
#include	<string>
#include	<vector>


using namespace std;

const unsigned int	kUIntLimit = 100000000U;
const unsigned int	kUIntLimitDigitNum = 8U;

int	parseSyntax(string& str, vector<vector<unsigned int>>& parsedVals);
bool	counter(vector<unsigned int>& count, vector<unsigned int>& counted);
void	displayResult(vector<unsigned int>& result);

int main(int argc, char* argv[])
{
	while (true)
	{
		string	line;

		vector<vector<unsigned int>> parsedVals;
		vector<unsigned int> result1;
		vector<unsigned int> result2;
		vector<unsigned int> result3;
		vector<unsigned int> factor;

		vector<unsigned int>*result1Ptr = &result1;
		vector<unsigned int>*result2Ptr = &result2;
		vector<unsigned int>*result3Ptr = &result3;

		unsigned long long	tempAdd = 0ULL;
		unsigned long long	tempCarry = 0ULL;

		vector<unsigned int> countedLine;

		if (argc == 1)
		{
			cout << "Input an exponential syntax (positive integers only) : ";
			cin >> line;
			if (!line.compare("exit"))
				break;
		}
		else if (argc == 2)
			line = string(argv[1]);
		int errorCode = parseSyntax(line, parsedVals);
		if (errorCode == 1)
		{
			cout << "Error : Wrong syntax." << endl;
			continue;
		}
		
		result3Ref = parsedVals[parsedVals.size() - 1];
		for (size_t i = parsedVals.size() - 2; i >= 0 && i != (size_t)-1; i--)
		{
			size_t	j = 0;

			factor = *result1Ptr = parsedVals[i];
			
			for (; j < result3Ptr->size() - 1 && result3Ptr->at(j) == 0U; j++)
				result3Ptr->at(j) = kUIntLimit - 1U;
			if (result3Ptr->at(j) == 1U && j == result3Ptr->size()s - 1)
				result3Ptr.pop_back();
			result3Ptr->at(j)--;

			countedLine.clear();

			while (counter(*result3Ptr, countedLine))
			{
				result2Ptr->clear();
				result2Ptr->push_back(0U);
				for (j = 0; j < factor.size(); j++)
				{
					tempCarry = 0ULL;

					size_t	k = 0;
					for (; k < result1Ptr->size(); k++)
					{
						tempAdd = (unsigned long long)factor[j] * (unsigned long long)result1Ref->at(k) + tempCarry;
						tempCarry = tempAdd / kUIntLimit;
						tempAdd %= kUIntLimit;
						if (result2Ptr->size() - 1 < j + k)
							result2Ptr->push_back(0U);
						if (result2Ptr->size() - 1 == j + k && tempCarry > 0ULL)
							result2Ptr->push_back(0U);
						tempCarry += (result2Ptr->at(j + k) + tempAdd) / kUIntLimit;
						result2Ptr->at(j + k) = (result2Ptr->at(j + k) + tempAdd) % kUIntLimit;
					}
					if (tempCarry > 0ULL)
						result2Ptr->at(j + k) += tempCarry;
				}
				swap(result2Ptr, result1Ptr);
			}
			swap(result1Ptr, result3Ptr);
		}
		displayResult(*result3Ptr);
		if (argc == 2)
			break;
	}

	return	0;
}

int parseSyntax(string& str, vector<vector<unsigned int>>& parsedVals)
{
	int	mul = 1;

	size_t	index1 = 0;
	size_t	index2 = 0;

	if (parsedVals.size() == 0)
		parsedVals.push_back(vector<unsigned int>());
	if (parsedVals[0].size() == 0)
		parsedVals[0].push_back(0U);
	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			if (mul == kUIntLimit)
			{
				mul = 1;
				parsedVals[index1].push_back(0U);
				index2++;
			}
			parsedVals[index1][index2] += mul * (str[i] - '0');
			mul *= 10;
		}
		else if (str[i] == '^')
		{
			mul = 1;
			parsedVals.push_back(vector<unsigned int>());
			index1++;
			parsedVals[index1].push_back(0U);
			index2 = 0;
		}
		else
			return	1;
	}

	return	0;
}

bool	counter(vector<unsigned int>& count, vector<unsigned int>& counted)
{
	size_t	i = 0;

	size_t	matchCount = 0;

	if (count.size() == 0)
		count.push_back(0U);
	if (counted.size() == 0)
		counted.push_back(0U);
	if (count.size() == counted.size())
	{
		for (size_t j = 0; j < count.size(); j++)
		{
			if (count[matchCount] == counted[matchCount])
				matchCount++;
			else
				break;
		}
		if (matchCount == count.size())
			return	false;
	}
	for (; counted[i] == kUIntLimit - 1U; i++)
	{
		counted[i] = 0U;
		if (counted.size() < i + 2)
			counted.push_back(0U);
	}
	counted[i]++;

	return	true;
}

void	displayResult(vector<unsigned int>& result)
{
	cout << result[result.size() - 1];
	for (size_t i = result.size() - 2; i >= 0 && i != (size_t)-1; i--)
	{
		unsigned int	tempVal = result[i];
		int	digitNum = 0;

		while (tempVal != 0)
		{
			tempVal /= 10U;
			digitNum++;
		}
		for (int j = 0; j < kUIntLimitDigitNum - digitNum; j++)
			cout << '0';
		if (digitNum != 0)
			cout << result[i];
	}
	cout << endl;
}
