int longestPalindrome(string s)
{
	int n=s.size();
	int pal[n][n];
	int maxLen=0;
	for (int i=0; i<n; i++)
	{
		int j=i;
		while (j>=0)
		{
			if (s[j]==s.[i]&&(i-j<2||pal[j+1][i-1]))
			{
				pal[j][i]=true;
				maxLen=max(maxLen, i-j+1);
			}
			j--;
		}
	}
	return maxLen;
}
