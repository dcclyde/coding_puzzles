from datetime import date, datetime

import pandas
from io import StringIO

def diff_days(csv_contents: str) -> int:
    csv_object = pandas.read_csv(StringIO(csv_contents))
    # print(csv_object)
    for a, b in csv_object.loc[:, 'Date']:
    print(csv_object.loc[:,'Date'])
    # for q in csv_object:
    #     print(q[:,'Date'])


    return
    csv_contents = csv_contents.strip()
    per_row = csv_contents.split('\n')
    fields = [q.split(',') for q in per_row]
    header = fields[0]
    date_col = 0
    while date_col < len(header) and header[date_col] != 'Date':
        date_col += 1

    min_date = None
    max_date = None
    for k in range(1, len(fields)):
#         print(k, fields[k], fields[k][date_col])
        date = datetime.strptime(fields[k][date_col], '%Y-%m-%d')
        if min_date is None:
            min_date = date
            max_date = date
        else:
            min_date = min(date, min_date)
            max_date = max(date, max_date)

    return (max_date - min_date).days


# Examples
print(diff_days("Date,Price,Volume\n2014-01-27,550.50,1387\n2014-06-23,910.83,4361\n2014-05-20,604.51,5870"))
print(diff_days('Date\n2000-01-01\n2000-01-01\n'))

# The last expression evaluated is always shown when
# you run your code, just like a Jupyter notebook cell.
"Good luck!"
