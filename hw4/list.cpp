void listAll(string path, const File* f)  // two-parameter overload
{

    if (f->files() == nullptr)
    {
        cout << path << endl;

        return;
    }

    cout << path << "/" << endl;
    
        path = path + '/';
    


    for (vector<File*>::const_iterator it = f->files()->begin(); it != f->files()->end(); it++)
    {


        listAll(path + (*it)->name(), (*it));
    }
}