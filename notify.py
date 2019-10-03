import inotify.adapters
import datetime;
import os


def main():
    time = datetime.datetime.now()
    next_time = time + datetime.timedelta(seconds=1)

    i = inotify.adapters.InotifyTree('./')

    monitored_types = ['IN_MODIFY', 'IN_DELETE', 'IN_CREATE']
    modified_files = set()

    for event in i.event_gen(yield_nones=False):
        (_, type_names, path, filename) = event
        # print(type_names)

        if filename.endswith('.cpp'):
            for t in monitored_types:
                if t in type_names:
                    modified_files.add(filename)

        time = datetime.datetime.now()

        if time >= next_time:
            if modified_files:
                print(modified_files)
                modified_files.clear()
                os.system('make all')

            next_time = time + datetime.timedelta(seconds=1)


if __name__ == '__main__':
    main()
