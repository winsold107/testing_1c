import sys
import os
import pkg_resources
import unittest
import subprocess as sp
import time
from balda.settings import BASE_DIR

manage = os.path.join(BASE_DIR, 'manage.py')


class TestStarter(unittest.TestCase):
    def test_venv(self):
        self.assertTrue(sys.prefix != sys.base_prefix)

    def test_reqs(self):
        reqs = os.path.join(BASE_DIR, 'requirements.txt')
        with open(reqs) as r:
            rs = r.readlines()
            for i in rs:
                i = i.split('\n')[0]

        pkg_resources.require(rs)

    def test_initial_migrations(self):
        proc1 = sp.call(f"python {manage} makemigrations", shell=True)
        proc2 = sp.call(f"python {manage} migrate", shell=True)
        self.assertTrue(proc1 == 0 & proc2 == 0)

    def test_game_migrations(self):
        proc1 = sp.call(f"python {manage} makemigrations balda_game", shell=True)
        proc2 = sp.call(f"python {manage} migrate balda_game", shell=True)
        self.assertTrue(proc1 == 0 & proc2 == 0)

    def test_server(self):
        try:
            proc = sp.run(f"python {manage} runserver", shell=True, stdout=sp.PIPE, stderr=sp.PIPE)
            stderr = proc.stderr
        except sp.CalledProcessError as e:
            print(e.message)


if __name__ == '__main__':
    unittest.main()
