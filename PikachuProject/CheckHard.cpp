#include "CheckHard.h"
#include"DifficultMode.h"




CELL_2* findTheNode(CELL_2** arr, int y, int x)
{
    if (y < 0 || y > 4 || x < 0 || x > 7) return NULL;

    CELL_2* temp = arr[y];
    while (temp != NULL) {
        if (temp->j == x) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

bool Icheck(CELL_2** arr, int y1, int x1, int y2, int x2) //check if 2 heads of a line exist no more than 2 valid boxes
{
    int ma, mi, i = 0;
    CELL_2* temp, * tempHead;
    if (x1 == x2)
    {
        ma = max(y1, y2);
        mi = min(y1, y2);
        tempHead = findTheNode(arr, mi, x1);
        temp = tempHead;
        while (temp == NULL)
        {
            mi++;
            temp = findTheNode(arr, mi, x1);
            tempHead = temp;
            if (mi == ma)
            {
                return true;
            }
            if (temp != NULL)
            {
                return false;
            }
        }
        while (temp != NULL)
        {
            i++;
            temp = findTheNode(arr, mi + i, x1);
            while (temp == NULL)
            {
                i++;
                temp = findTheNode(arr, mi + i, x1);
                if (mi + i > ma)
                {
                    return true;
                }
            }
            if (mi + i > ma)
            {
                return true;
            }
            if (mi + i == ma)
            {
                if (temp == NULL)
                {
                    return true;
                }
                if (temp->c == tempHead->c)
                {
                    return true;
                }
                return false;
            }
            if (temp != NULL)
            {
                return false;
            }
        }
    }
    if (y1 == y2)
    {
        i = 0;
        ma = max(x1, x2);
        mi = min(x1, x2);
        tempHead = findTheNode(arr, y1, mi);
        temp = tempHead;
        while (temp == NULL)
        {
            mi++;
            temp = findTheNode(arr, mi, x1);
            tempHead = temp;
            if (mi > ma) 
            {
                return true;
            }
        }
        while (temp != NULL) 
        {
            i++;
            temp = temp->next;
            if (mi + i > ma)
            {
                return true;
            }
            if (mi + i == ma) 
            {
                if (temp == NULL) 
                {
                    return true;
                }
                if (temp->c == tempHead->c)
                {
                    return true;
                }
                return false;
            }
            if (temp != NULL)
            {
                return false;
            }
        }
    }
    return false;
}

bool Lcheck(CELL_2** arr, int y1, int x1, int y2, int x2, int &cory, int &corx) 
{
    CELL_2* cor = findTheNode(arr, y1, x2);
    if (!cor)
    {
        if (Icheck(arr, y1, x1, y1, x2) && Icheck(arr, y1, x2, y2, x2))
        {
            cory = y1;
            corx = x2;
            return true;
        }
    }
    else
        cor = findTheNode(arr, y2, x1);
    if (!cor)
    {
        if (Icheck(arr, y1, x1, y2, x1) && Icheck(arr, y2, x2, y2, x1))
        {
            cory = y2;
            corx = x1;
            return true;
        }
    }


    return false;
}


bool Ucheck(CELL_2** arr, int y1, int x1, int y2, int x2)
{
    if ((findTheNode(arr, y1 - 1, x1) == nullptr && findTheNode(arr, y2 - 1, x2) == nullptr || findTheNode(arr, y1 + 1, x1) == nullptr && findTheNode(arr, y2 + 1, x2) == nullptr) && (y1 == y2))
    {
        return true;
    }
    //on the same row and there is no valid box under/above them

    if ((x1 == 0 && x2 == 0) || (findTheNode(arr, y1, x1)->next == nullptr && findTheNode(arr, y2, x2)->next == nullptr))
    {
        return true;
    }
    //both are on the first col/ their last col 

    int ma, mi;
    ma = max(y1, y2);
    mi = min(y1, y2);
    if (x1 != x2) 
    {
        for (int i = 0; (i < BOARDHEIGHT); i++)
        {
            if (i<mi || i>ma)
            {
                if (Icheck(arr, i, x1, i, x2))
                {
                    if (Icheck(arr, i, x1, y1, x1) && Icheck(arr, i, x2, y2, x2))
                    {
                        return true;
                    }
                }
            }
        }
    }

    ma = max(x1, x2);
    mi = min(x1, x2);
    if (y1 != y2)
    {
        for (int i = 0; i < BOARDHEIGHT; i++) 
        {
            if (i<mi || i>ma)
            {
                if (Icheck(arr, y1, i, y2, i))
                {
                    if (Icheck(arr, y1, i, y1, x1) && Icheck(arr, y2, i, y2, x2))
                    {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}


bool Zcheck(CELL_2** arr, int y1, int x1, int y2, int x2, int& cory1, int& corx1, int& cory2, int& corx2)
{
    if (x1 == x2 || y1 == y2)
    {
        return false;       //if they r both on the same row or same col, it is not the Z type
    }

    int ma, mi;
    ma = max(y1, y2);
    mi = min(y1, y2);
    if (x1 != x2) {
        for (int i = mi+1; i < ma; i++)
        {
            if (Icheck(arr, i, x1, i, x2))
            {
                if (Icheck(arr, i, x1, y1, x1) && Icheck(arr, i, x2, y2, x2))
                {
                    cory1 = i;
                    corx1 = x1;
                    corx2 = x2;
                    cory2 = cory1;
                    return true;
                }
            }
        }
    }

    ma = max(x1, x2);
    mi = min(x1, x2);
    if (y1 != y2)
    {
        for (int i = mi+1; i < ma; i++)
        {
            if (Icheck(arr, y1, i, y2, i))
            {
                if (Icheck(arr, y1, i, y1, x1) && Icheck(arr, y2, i, y2, x2))
                {
                    cory1 = y1;
                    cory2 = y2;
                    corx1 = i;
                    corx2 = corx1;
                    return true;
                }
            }
        }
    }

    return false;

}









int allCheck(CELL_2** arr, int y1, int x1, int y2, int x2, int cory1, int corx1, int cory2, int corx2)
{
    if (Icheck(arr, y1, x1, y2, x2))
        return 1;
    else if (Lcheck(arr, y1, x1, y2, x2,cory1, corx1))
        return 2;
    else if (Ucheck(arr, y1, x1, y2, x2))
        return 3;
    else if (Zcheck(arr, y1, x1, y2, x2, cory1, corx1, cory2, corx2))
        return 4;
    return 0;
}


bool checkValidPairs(CELL_2** arr)
{
    CELL_2* Head, * temp;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int i = 0; i < 5; i++)
    {
        Head = arr[i];
        while (Head != NULL)
        {
            int j = i;
            temp = Head->next;
            while (temp == NULL && j < 4)
            {
                j++;
                temp = arr[j];
            }
            while (temp != NULL)
            {
                if (Head->c == temp->c)
                {
                    if (allCheck(arr, Head->i, Head->j, temp->i, temp->j,c1,c2,c3,c4))
                    {
                        return true;
                    }
                }
                temp = temp->next;
                if ((temp == NULL) && (j < 4)) {
                    j++;
                    temp = findTheNode(arr, j, 0);
                }
            }
            Head = Head->next;
        }
    }
    return false;
}

void suggest(CELL_2** arr)
{
    CELL_2* Head, * temp;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int i = 0; i < 5; i++)
    {
        Head = arr[i];
        while (Head != NULL)
        {
            int j = i;
            temp = Head->next;
            while (temp == NULL && j < 4)
            {
                j++;
                temp = arr[j];
            }
            while (temp != NULL)
            {
                if (Head->c == temp->c)
                {
                    if (allCheck(arr, Head->i, Head->j, temp->i, temp->j,c1,c2,c3,c4))
                    {
                        CELL_2* p1 = findTheNode(arr, Head->i, Head->j);
                        CELL_2* p2 = findTheNode(arr, temp->i, temp->j);
                        p1->isSelected = 1;
                        p2->isSelected = 1;
                        p1->drawBox(50);
                        p2->drawBox(50);
                        Sleep(1250);

                        p1->isSelected = 0;
                        p2->isSelected = 0;
                        return;
                    }
                }
                temp = temp->next;
                if ((temp == NULL) && (j < 4)) {
                    j++;
                    temp = findTheNode(arr, j, 0);
                }
            }
            Head = Head->next;
        }
    }
}

