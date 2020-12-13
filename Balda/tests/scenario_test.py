import unittest
from balda_game.forms import CreationUserForm
from datetime import datetime
from django.test import TestCase
from django.contrib.auth.models import User
from django.core.cache import cache
from balda_game.models import UserPlayer


form = CreationUserForm.CreationUserForm(data={
            'username': 'user',
            'first_name': 'john',
            'last_name': 'doe',
            'password1': '12345678',
            'password2': '12345678'
})

user = User.objects.create_user(
    username='user',
    email='user@google.com',
    password='12345678'
)

user_player = UserPlayer.objects.create(
    user=user,
    wins=0, draws=0, loses=0, rating=0, was_online=datetime.now()
)


class TestScenario(TestCase):

    def test_form(self):
        self.assertTrue(form.is_valid())
        form.save(commit=True)
        try:
            user = User.objects.get(username='user')
            UserPlayer.objects.get(user=user)
        except (User.DoesNotExist, UserPlayer.DoesNotExist):
            print("user failed")

    def test_user(self):
        player = UserPlayer.objects.get(id=user_player.id)
        self.assertTrue(str(player) == 'user Wins: 0 Draws: 0 Loses: 0 Rating: 0')

        now = datetime.now()
        cache.set('seen_user', now, 10)
        self.assertTrue(user_player.last_seen() == now)

        cache.set('seen_1_user', now, 10)
        self.assertTrue(user_player.last_seen_in_game(1) == now)

    def test_register(self):
        response = self.client.get('register')
        self.assertTrue(response.status_code == 200)

        response = self.client.post(
            'register', data={
                'username': 'user',
                'first_name': 'john',
                'second_name': 'doe',
                'password1': '12345678',
                'password2': '12345678'
            }
        )
        self.assertTrue(response.status_code == 200)

    def test_login(self):
        response = self.client.get('login_view')
        self.assertTrue(response.status_code == 200)
        self.user_player = user_player
        response = self.client.post('login_view', data={
                'username': 'user',
                'password': '12345678'}, follow=True)
        self.assertTrue(self.user_player.user.is_active)
        self.assertTrue(self.user_player.last_seen() >= datetime.now())

    def test_play(self):
        self.client.login(username='user', password='12345678')
        response = self.client.get('play_with_bot')
        self.assertTrue(response.status_code == 200)


if __name__ == '__main__':
    unittest.main()