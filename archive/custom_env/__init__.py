import logging
from gym.envs.registration import register

logger = logging.getLogger(__name__)

register(
    id='Multiagent-v0',
    entry_point='custom_env.custom_env_test:MultiAgent',
)